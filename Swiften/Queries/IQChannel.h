/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <memory>
#include <string>

#include <Swiften/Base/API.h>
#include <Swiften/Base/boost_bsignals.h>
#include <Swiften/Elements/IQ.h>

namespace Swift {
    class SWIFTEN_API IQChannel {
        public:
            virtual ~IQChannel();

            virtual void sendIQ(std::shared_ptr<IQ>) = 0;
            virtual std::string getNewIQID() = 0;

            virtual bool isAvailable() const = 0;

            boost::signal<void (std::shared_ptr<IQ>)> onIQReceived;
    };
}
