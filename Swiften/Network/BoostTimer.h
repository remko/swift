/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Swiften/EventLoop/EventOwner.h"
#include "Swiften/Network/Timer.h"

namespace Swift {
	class BoostTimer : public Timer, public EventOwner, public boost::enable_shared_from_this<BoostTimer> {
		public:
			typedef boost::shared_ptr<BoostTimer> ref;

			static ref create(int milliseconds, boost::asio::io_service* service) {
				return ref(new BoostTimer(milliseconds, service));
			}

			virtual void start();
			virtual void stop();

		private:
			BoostTimer(int milliseconds, boost::asio::io_service* service);

			void handleTimerTick(const boost::system::error_code& error);

		private:
			int timeout;
			boost::asio::deadline_timer timer;
	};
}
