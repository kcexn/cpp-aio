/*     
*	Copyright 2024 Kevin Exton
*	This file is part of cpp-aio.
*
* cpp-aio is free software: you can redistribute it and/or modify it under the 
*	terms of the GNU General Public License as published by the Free Software 
*	Foundation, either version 3 of the License, or any later version.
*
* cpp-aio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
*	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*	See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with cpp-aio. 
*	If not, see <https://www.gnu.org/licenses/>. 
*/
#include "io.hpp"
#include <poll.h>
namespace io{
	poller::size_type poller::_add(native_handle_type handle, events_type& events, event_type event){
		auto it = std::find_if(events.cbegin(), events.cend(), [&](const auto& ev){ return ev.fd == handle; });
		if(it != events.cend()) return npos;
		events.push_back(event);
		return events.size();
	}
	
	poller::size_type poller::_update(native_handle_type handle, events_type& events, event_type event){
		auto it = std::find_if(events.begin(), events.end(), [&](auto& ev) { return ev.fd == handle; });
		if(it == events.end()) return npos;
		it->events = event.events;
		return events.size();
	}
	
	poller::size_type poller::_del(native_handle_type handle, events_type& events){
		auto it = std::find_if(events.cbegin(), events.cend(), [&](const auto& ev){ return ev.fd == handle; });
		if(it == events.cend()) return npos;
		events.erase(it);
		return events.size();
	}
	
	
	poller::size_type poller::_poll(duration_type timeout){
		int nfds = 0;
		if((nfds = poll(Base::events(), Base::size(), timeout.count())) < 0) return npos;
		return nfds;
	}
	
	trigger::event_type trigger::mkevent(native_handle_type handle, trigger_type trigger){
		event_type event = {};
		event.fd = handle;
		event.events = trigger;
		return event;
	}
}
