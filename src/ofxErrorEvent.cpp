#include "ofxErrorEvent.h"
#include <ofLog.h>
#include <ofEventUtils.h>
#include <sstream>

namespace ofxErrorEvent {
// EventArgs
EventArgs::EventArgs()
 : source(0),
   type(0),
   id(0),
   severity(0),
   length(0),
   message(nullptr),
   userParam(nullptr) {
}
std::string EventArgs::toString() const {
	std::stringstream ss;
	ss << "source=" << source << " type=" << type << " id=" << id << " serverity=" << severity << " length=" << length << " message" << message;
	return ss.str();
}
// Handler
std::shared_ptr<Handler> Handler::instance = nullptr;
std::shared_ptr<Handler> Handler::setup(const void* userParam) {
	if (Handler::instance == nullptr) {
		Handler::instance = std::shared_ptr<Handler>(new Handler());
		ofAddListener(Handler::instance->m_event, Handler::instance.get(), &Handler::onError);
	} else {
		ofLogWarning() << "ofxErrorEvent was already setup.";
	}
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(detail::onError, userParam);
	return Handler::instance;
}
std::shared_ptr<Handler> Handler::setup() {
	return setup(nullptr);
}
std::shared_ptr<Handler> Handler::getHandler() {
	return Handler::instance;
}
ofEvent<EventArgs>& Handler::getEvent() {
	return this->m_event;
}
std::vector<Callback>& Handler::startUpdateCallbackList() {
	m_mutex.lock();
	return this->m_listenerList;
}
void Handler::endUpdateCallbackList() {
	m_mutex.unlock();
}
void Handler::onError(EventArgs& e) {
	std::lock_guard<std::recursive_mutex> l(m_mutex);
	for (auto listener : m_listenerList) {
		listener(e);
	}
}
// private
Handler::Handler() : m_listenerList(), m_event(), m_mutex() {
}

// ::detail
namespace detail {
void GLAPIENTRY onError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam) {
	EventArgs a;
	a.source = source;
	a.type = type;
	a.id = id;
	a.severity = severity;
	a.length = length;
	a.message = message;
	a.userParam = userParam;
	auto hdr = Handler::getHandler();
	if (hdr != nullptr) {
		ofNotifyEvent(hdr->getEvent(), a);
	}
}
}
}

