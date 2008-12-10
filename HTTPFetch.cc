/* --------------------------------------------------------------------------

   flactag -- A tagger for single album FLAC files with embedded CUE sheets
   						using data retrieved from the MusicBrainz service

   Copyright (C) 2006 Andrew Hawkins

   This file is part of flactag.

   Flactag is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id: MusicBrainzInfo.cc 163 2008-12-05 16:35:32Z flactag $

----------------------------------------------------------------------------*/

#include "HTTPFetch.h"

#include "ne_session.h"
#include "ne_string.h"
#include "ne_request.h"

CHTTPFetch::CHTTPFetch()
{
}

int CHTTPFetch::Fetch(const std::string& URL)
{
	int Ret=0;
	
	m_Data.clear();
			
	ne_uri uri={0};
	
	if (0==ne_uri_parse(URL.c_str(), &uri))
	{
		if (uri.port == 0)
			uri.port = ne_uri_defaultport(uri.scheme);

		ne_sock_init();
	
		ne_session *sess=ne_session_create("http", uri.host, uri.port);
		if (sess) 
		{
			ne_set_useragent(sess, "flactag/v" VERSION);
	
			ne_request *req = ne_request_create(sess, "GET", uri.path);	
			ne_add_response_body_reader(req, ne_accept_2xx, httpResponseReader, &m_Data);

			m_Result = ne_request_dispatch(req);
			m_Status = ne_get_status(req)->code;

			Ret=m_Data.size();
			
			ne_request_destroy(req); 
	
			m_ErrorMessage = ne_get_error(sess);

			ne_session_destroy(sess);
		}
	}
	
	return Ret;
}

int CHTTPFetch::httpResponseReader(void *userdata, const char *buf, size_t len)
{
	std::vector<unsigned char> *buffer = reinterpret_cast<std::vector<unsigned char> *>(userdata);

	for (size_t count=0;count<len;count++)
		buffer->push_back(buf[count]);

	return 0;
}

std::vector<unsigned char> CHTTPFetch::Data() const
{
	return m_Data;
}

int CHTTPFetch::Result() const
{
	return m_Result;
}

int CHTTPFetch::Status() const
{
	return m_Status;
}

std::string CHTTPFetch::ErrorMessage() const
{
	return m_ErrorMessage;
}
