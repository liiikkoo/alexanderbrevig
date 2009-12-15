#ifndef PUSHPOP_H
#define PUSHPOP_H


namespace ab {
	template<typename T>
	class PushPop {
	public:
		virtual ~PushPop() {}
		virtual bool	push			( T ) = 0;			//push an item into the Storage
		virtual bool	push			( unsigned int, T ) { return false; }
		virtual T		pop				( void ) = 0;		//pop an element from the Storage [specify rules]
	};
}

#endif