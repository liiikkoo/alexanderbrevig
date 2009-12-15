#ifndef TAG_H
#define TAG_H

#include <string>
using std::string;

#include <deque>
using std::deque;

#include "Log.h"
#include "Attribute.h"

namespace ab {
	namespace xml {
		class Tag {
		public:
			Tag( Tag *newParent = 0 );
			virtual ~Tag();

			void			setLevel( unsigned char newLevel );
			unsigned char	getLevel();
			void			setName( const char *name );
			const char*		getName();
			void			setValue( const char *name );
			const char*		getValue();

			void			addAttribute( Attribute *newAttribute );
			unsigned char	hasAttributes();
			Attribute*		getAttribute( unsigned int index );

			void			setParent( Tag *newParent );
			Tag*			getParent();

			void			addChild( Tag *newChild );
			Tag&			operator[]( unsigned int index );

			void			print();

		protected:
			unsigned char level;
			string name;
			string value;
			deque<Attribute*> attributes;
			Tag *parent;
			deque<Tag*> children;
		private:
			void pad();
		};
	}
}

ab::xml::Tag::Tag(ab::xml::Tag *newParent) : parent(newParent) {
	LOG(Log::LOG_INFO, "Constructing");
	if (parent==0){
		level = 0;
	} else {
		level = parent->getLevel() + 1;
		parent->addChild(this);
	}
}
ab::xml::Tag::~Tag() {
	LOG(Log::LOG_INFO, "Destructing");
	//DO NOT delete parent
	unsigned int size = attributes.size();
	for (unsigned int i=0; i<size; i++) {
		delete attributes.at(i);
	}
	size = children.size();
	for (unsigned int i=0; i<size; i++) {
		delete children.at(i);
	}
	name.clear();	//safety
	value.clear();
}


void ab::xml::Tag::setLevel( unsigned char newLevel )
	{ level = newLevel; }
unsigned char ab::xml::Tag::getLevel() 
	{ return level; }
void ab::xml::Tag::setName( const char *newName )
	{ name=newName; }
const char* ab::xml::Tag::getName()
	{ return name.c_str(); }
void ab::xml::Tag::setValue( const char *newValue )
	{ value = newValue; }
const char* ab::xml::Tag::getValue()
	{ return value.c_str(); }

void ab::xml::Tag::addAttribute( ab::xml::Attribute *newAttribute )
	{ attributes.push_back(newAttribute); }
unsigned char ab::xml::Tag::hasAttributes()
	{ return (unsigned char)attributes.size(); }
ab::xml::Attribute* ab::xml::Tag::getAttribute( unsigned int index ){ 
	if (attributes.size()>0 && index<attributes.size()){
		return attributes.at(index); 
	} 
	return 0;
}

void ab::xml::Tag::setParent( Tag *newParent ){ parent = newParent; }
ab::xml::Tag* ab::xml::Tag::getParent(){ return parent; }

void ab::xml::Tag::addChild( ab::xml::Tag *newChild ){ 
	children.push_back(newChild);
}
ab::xml::Tag& ab::xml::Tag::operator[]( unsigned int index ){
	return *children.at(index); 
}
/*
Print tag to console
*/
void ab::xml::Tag::print(){
	pad();
	cout << "<" << name;
	unsigned int size = attributes.size();
	for (unsigned int i=0; i<size; i++) {
		attributes.at(i)->print();
	}
	cout << ">";
	if (value.length()<=0){ 
		cout << endl; 
		size = children.size();
		for (unsigned int i=0; i<size; i++) {
			children.at(i)->print();
		}
	} else {
		cout << value;
	}
	if (value.length()<=0){
		pad();
	}
	cout << "</" << name << ">" << endl;
}
void ab::xml::Tag::pad(){
	for (unsigned char i=0; i<level; i++){
		cout << "\t";
	}
}

#endif