#ifndef XMLREADER_H
#define XMLREADER_H

#include <iostream>
#include <fstream>
#include <string>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;	

#include "Log.h"
#include "Tag.h"
#include "Attribute.h"
#include "XMLAble.h"
#include "Stack.h"

namespace ab {
	namespace xml {
		class XMLReader {
		public:
			XMLReader();
			virtual ~XMLReader();

			bool read(Tag *root, const char* infileName);
			bool write(XMLAble *root, const char* outfileName);

		protected:
			ifstream infile;
			ofstream outinfile;
		};
	}
}

ab::xml::XMLReader::XMLReader() {
	LOG(Log::LOG_INFO, "Constructing");
}
ab::xml::XMLReader::~XMLReader() {
	LOG(Log::LOG_INFO, "Destructing");
}

bool ab::xml::XMLReader::read(ab::xml::Tag *root, const char* infileName) {
	infile.open( infileName , std::ios::in );

	string line;

	static const char TAG_OPEN = '<';
	static const char TAG_END_OPEN = '/';
	static const char TAG_CLOSE = '>';
	static const char COMMENT= '!';

	static bool insideTag = true;
	static bool doneSettingRoot = false;
	Tag *current = root;

	ab::Stack<Tag*> previous;
	previous.push( current );

	bool success = true;

	if (infile.is_open()){
		while ( ! infile.eof() ){
			//TODO multiline comments
			getline( infile, line );
			unsigned int length = line.length();
			for (unsigned int i=0; i<length; i++){
				//cout << line.at(i);
				if (line.at(i)=='\t'){
					//skip tabs
				} else if (line.at(i)==TAG_OPEN){
					if (line.at(i+1)==TAG_END_OPEN){
						string tagName;
						unsigned char j = i+2;
						char rec = line.at(j);
						do {
							tagName += rec;
							rec = line.at(++j);
						} while (rec!=TAG_CLOSE && rec!=' ' && rec!='\t');						
						i = j; //skip the already parsed section
						current = previous.pop(); //go back to parent
					} else if (line.at(i+1)==COMMENT){
						//TODO multiline
						unsigned char j = i+1;
						char rec = line.at(j);
						do { rec = line.at(++j); } while (rec!=TAG_CLOSE);
						i = j;
					} else {
						//start of new tag
						string tagName;
						unsigned char j = i+1;
						char rec = line.at(j);
						do {
							tagName += rec;
							rec = line.at(++j);
						} while (rec!=TAG_CLOSE && rec!=' ' && rec!='\t');
						
						if (doneSettingRoot){
							previous.push(current);
							current = new Tag(previous.get());
						}
						current->setName(tagName.c_str());
						doneSettingRoot = true;

						//next tag
						i = j-1;
						insideTag = true;
					}
				} else if (line.at(i)==TAG_CLOSE){
					insideTag = false;
					//doneSettingRoot = true;
				} else if (insideTag && line.at(i)==' ' ) {
					string attr;
					unsigned char j = i+1;
					char rec = line.at(j);
					do {
						attr += rec;
						rec = line.at(++j);
					} while (rec!=' ' && rec!='\t' && rec!=TAG_CLOSE && rec!=TAG_OPEN );
					
					//skip the already parsed section
					i = j-1;

					string attrName;
					for (j=0; attr.at(j)!='='; j++){
						if (j+1>=attr.length()){
							cout << "Attribute parsing error [need id=val]" << endl;
							success = false;
							break;
						} else {
							attrName += attr.at(j);
						}
					}

					string attrValue;
					for (; attr.at(j)!=' ' && attr.at(j)!=TAG_CLOSE; j++){
						if (j+1>=attr.length()){
							break;
						} else if (attr.at(j)=='='||attr.at(j)=='"'){
							//skip
						} else {
							attrValue += attr.at(j);
						}
					}
					Attribute *attribute = new Attribute();
					attribute->name = attrName;
					attribute->value = attrValue;
					current->addAttribute( attribute );
				} else {
					string value;
					unsigned char j = i;
					char rec = line.at(j);
					do {
						value += rec;
						if (j+1>=line.length()){ ++j; break; }
						rec = line.at(++j);
					} while (rec!=TAG_CLOSE && rec!=TAG_OPEN );
					i = j-1;
					current->setValue( value.c_str() );
				}
			}
		}
		infile.close();
	}
	return success;
}

bool ab::xml::XMLReader::write( ab::xml::XMLAble *root, const char* outfileName) {
	outfile.open( outfileName  );
	outfile << "XMLReader::write:" << endl << *root << endl;
	outfile.close();
	bool success = true;
	return success;
}

#endif