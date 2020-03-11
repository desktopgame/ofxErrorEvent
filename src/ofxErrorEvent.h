#pragma once
#ifndef OFXERROREVENT_H
#define OFXERROREVENT_H
#include <functional>
#include <memory>
#include <string>
#include <mutex>
#include <ofEvent.h>
#include <ofTypes.h>

namespace ofxErrorEvent {
/**
 * Event.
 */
struct EventArgs {
	explicit EventArgs();
	std::string toString() const;

	GLenum source;
	GLenum type;
	GLuint id;
	GLenum severity;
	GLsizei length;
	const GLchar* message;
	const void* userParam;
};

/**
 * Callback.
 */
using Callback = std::function<void(EventArgs)>;

/**
 * Handler.
 */
class Handler {
public:
	/**
	 * setup a ofxErrorEvent.
	 * should be call this in setup().
	 * @parma userParam
	 */
	static std::shared_ptr<Handler> setup(const void* userParam);
	/**
	 * setup a ofxErrorEvent.
	 * should be call this in setup().
	 */
	static std::shared_ptr<Handler> setup();

	/**
	 * returns handler instance.
	 * @return
	 */
	static std::shared_ptr<Handler> getHandler();

	/**
	 * returns event for handling error.
	 * @return
	 */
	ofEvent<EventArgs>& getEvent();

	/**
	 * returns callback list.
	 * should be call endUpdateCallbackList() at after call this function.
	 * @return
	 */
	std::vector<Callback>& startUpdateCallbackList();

	/**
	 * terminate a synchronization.
	 */
	void endUpdateCallbackList();
private:
	void onError(EventArgs& e);
	Handler();
	static std::shared_ptr<Handler> instance;
	ofEvent<EventArgs> m_event;
	std::vector<Callback> m_listenerList;
	std::recursive_mutex m_mutex;
};

namespace detail {
/**
 * @param source
 * @param type
 * @param id
 * @param serverity
 * @param length
 * @param message
 * @param userParam
 */
void GLAPIENTRY onError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
}
}
#endif