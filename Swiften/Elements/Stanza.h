/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <string>
#include <vector>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/optional/optional.hpp>
#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Elements/ToplevelElement.h>
#include <Swiften/JID/JID.h>

namespace Swift {
	class Payload;

	class SWIFTEN_API Stanza : public ToplevelElement {
		public:
			typedef boost::shared_ptr<Stanza> ref;

		protected:
			Stanza();

		public:
			virtual ~Stanza();
			SWIFTEN_DEFAULT_COPY_CONSTRUCTOR(Stanza)

			template<typename T> 
			boost::shared_ptr<T> getPayload() const {
				for (size_t i = 0; i < payloads_.size(); ++i) {
					boost::shared_ptr<T> result(boost::dynamic_pointer_cast<T>(payloads_[i]));
					if (result) {
						return result;
					}
				}
				return boost::shared_ptr<T>();
			}

			template<typename T> 
			std::vector< boost::shared_ptr<T> > getPayloads() const {
				std::vector< boost::shared_ptr<T> > results;
				for (size_t i = 0; i < payloads_.size(); ++i) {
					boost::shared_ptr<T> result(boost::dynamic_pointer_cast<T>(payloads_[i]));
					if (result) {
						results.push_back(result);
					}
				}
				return results;
			}


			const std::vector< boost::shared_ptr<Payload> >& getPayloads() const {
				return payloads_;
			}

			void addPayload(boost::shared_ptr<Payload> payload) {
				payloads_.push_back(payload);
			}

			template<typename InputIterator>
			void addPayloads(InputIterator begin, InputIterator end) {
				payloads_.insert(payloads_.end(), begin, end);
			}

			void updatePayload(boost::shared_ptr<Payload> payload);

			void removePayloadOfSameType(boost::shared_ptr<Payload>);
			boost::shared_ptr<Payload> getPayloadOfSameType(boost::shared_ptr<Payload>) const;

			const JID& getFrom() const { return from_; }
			void setFrom(const JID& from) { from_ = from; }

			const JID& getTo() const { return to_; }
			void setTo(const JID& to) { to_ = to; }

			const std::string& getID() const { return id_; }
			void setID(const std::string& id) { id_ = id; }

			boost::optional<boost::posix_time::ptime> getTimestamp() const;

			// Falls back to any timestamp if no specific timestamp for the given JID is found.
			boost::optional<boost::posix_time::ptime> getTimestampFrom(const JID& jid) const;
	
		private:
			std::string id_;
			JID from_;
			JID to_;
			std::vector< boost::shared_ptr<Payload> > payloads_;
	};
}
