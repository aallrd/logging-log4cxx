/***************************************************************************
                          nullappender.h  -  class NullAppender
                             -------------------
    begin                : 2003/09/12
    copyright            : (C) 2003 by Michael CATANZARITI
    email                : mcatan@free.fr
 ***************************************************************************/

/***************************************************************************
 * Copyright (C) The Apache Software Foundation. All rights reserved.      *
 *                                                                         *
 * This software is published under the terms of the Apache Software       *
 * License version 1.1, a copy of which has been included with this        *
 * distribution in the LICENSE.txt file.                                   *
 ***************************************************************************/

#ifndef _LOG4CXX_PERFORMANCE_NULL_APPENDER_H
#define _LOG4CXX_PERFORMANCE_NULL_APPENDER_H

#include <log4cxx/config.h>
#include <log4cxx/helpers/tchar.h>
#include <log4cxx/appenderskeleton.h>


namespace log4cxx
{
	namespace spi
	{
		class LoggingEvent;
	};

	class Layout;
	typedef helpers::ObjectPtrT<Layout> LayoutPtr;

	namespace performance
	{
		class NullAppender;
		typedef helpers::ObjectPtrT<NullAppender> NullAppenderPtr;

		/**
		* A bogus appender which calls the format method of its layout object
		* but does not write the result anywhere.
		* */
		class NullAppender : public AppenderSkeleton
		{
		public:
			static String s;

			DECLARE_LOG4CXX_OBJECT(NullAppender)
			BEGIN_LOG4CXX_CAST_MAP()
				LOG4CXX_CAST_ENTRY(NullAppender)
				LOG4CXX_CAST_ENTRY_CHAIN(AppenderSkeleton)
			END_LOG4CXX_CAST_MAP()

			NullAppender();
			NullAppender(LayoutPtr layout);
			void close();
			void doAppend(const spi::LoggingEvent& event);
			void append(const spi::LoggingEvent& event);

			/**
			This is a bogus appender but it still uses a layout.
			*/
			bool requiresLayout();
		}; // NullAppender
	}; // namespace performance
}; // namespace log4cxx

#endif //_LOG4CXX_PERFORMANCE_NULL_APPENDER_H