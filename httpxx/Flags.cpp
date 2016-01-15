// Copyright(c) Andre Caron <andre.l.caron@gmail.com>, 2011
//
// This document is covered by the an Open Source Initiative approved license. A
// copy of the license should have been provided alongside this software package
// (see "LICENSE.txt"). If not, terms of the license are available online at
// "http://www.opensource.org/licenses/mit".

#include "Flags.hpp"

namespace http {
	Flags::Flags() : myValue(Flags::Value(0))
	{

	}

	Flags::Flags(const Flags& flags) : myValue(flags.myValue)
	{

	}

	Flags::Flags(Value value) : myValue(value)
	{

	}

	void Flags::set_chunked(bool chunked)
	{
		if(chunked)
		{
			myValue = (Flags::Value)((int)myValue | F_CHUNKED);
		}
		else
		{
			myValue = (Flags::Value)((int)myValue | ~F_CHUNKED) ;
		}
	}

	void Flags::set_keepalive(bool keepalive)
	{
		if(keepalive)
		{
			myValue = (Flags::Value)((int)myValue | F_CONNECTION_KEEP_ALIVE);
		}
		else
		{
			myValue = (Flags::Value)((int)myValue | ~F_CONNECTION_KEEP_ALIVE) ;
		}
	}

	void Flags::set_close(bool close)
	{
		if(close)
		{
			myValue = (Flags::Value)((int)myValue | F_CONNECTION_CLOSE);
		}
		else
		{
			myValue = (Flags::Value)((int)myValue | ~F_CONNECTION_CLOSE) ;
		}
	}

	void Flags::set_trailing(bool trailing)
	{
		if(trailing)
		{
			myValue = (Flags::Value)((int)myValue | F_TRAILING);
		}
		else
		{
			myValue = (Flags::Value)((int)myValue | ~F_TRAILING) ;
		}
	}

	void Flags::set_upgrade(bool upgrade)
	{
		if(upgrade)
		{
			myValue = (Flags::Value)((int)myValue | F_UPGRADE);
		}
		else
		{
			myValue = (Flags::Value)((int)myValue | ~F_UPGRADE) ;
		}
	}

	void Flags::set_skipbody(bool skipbody)
	{
		if(skipbody)
		{
			myValue = (Flags::Value)((int)myValue | F_SKIPBODY);
		}
		else
		{
			myValue = (Flags::Value)((int)myValue | ~F_SKIPBODY) ;
		}
	}

    const Flags Flags::of ( const ::http_parser& parser )
    {
        return (static_cast< ::flags >(parser.flags));
    }

    const Flags Flags::chunked ()
    {
        return (F_CHUNKED);
    }

    const Flags Flags::keepalive ()
    {
        return (F_CONNECTION_KEEP_ALIVE);
    }

    const Flags Flags::close ()
    {
        return (F_CONNECTION_CLOSE);
    }

    const Flags Flags::trailing ()
    {
        return (F_TRAILING);
    }

    const Flags Flags::upgrade ()
    {
        return (F_UPGRADE);
    }

    const Flags Flags::skipbody ()
    {
        return (F_SKIPBODY);
    }
	    
    bool Flags::operator& ( const Flags& rhs ) const
    {
        return ((myValue & rhs.myValue) != 0);
    }

	http::Flags Flags::operator| ( const Flags& rhs ) const
	{
		return Flags((Value)(myValue | rhs.myValue));
	}

	http::Flags Flags::operator~ () const
	{
		return Flags((Value)(myValue));
	}

}
