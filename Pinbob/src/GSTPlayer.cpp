/*
 * GSTPlayer.cpp
 *
 *  Created on: Sep 24, 2011
 *      Author: yejiabin
 */

#include "GSTPlayer.h"
#include <gst/gst.h>
#include <pthread.h>
#include <stdlib.h>

static GMainLoop *songLoop;
static GstElement *songPipe;
static pthread_t songThread;

static gboolean bus_call(GstBus *bus, GstMessage *msg, void *user_data) {
	switch (GST_MESSAGE_TYPE(msg)) {
	case GST_MESSAGE_EOS: {
		g_message("End-of-stream");
		g_main_loop_quit(songLoop);
		pthread_exit(NULL);
		break;
	}
	case GST_MESSAGE_ERROR: {
		GError *err;
		gst_message_parse_error(msg, &err, NULL);
		g_error("%s", err->message);
		g_error_free(err);

		g_main_loop_quit(songLoop);
		pthread_exit(NULL);
		break;
	}
	default:
		break;
	}

	return true;
}

static void* startSongThread(void *uri) {
	GstBus *bus;

	songLoop = g_main_loop_new(NULL, FALSE);
	songPipe = gst_element_factory_make("playbin", "player");

	if (uri)
		g_object_set(G_OBJECT(songPipe), "uri", uri, NULL);

	bus = gst_pipeline_get_bus(GST_PIPELINE(songPipe));
	gst_bus_add_watch(bus, bus_call, NULL);
	gst_object_unref(bus);

	gst_element_set_state(GST_ELEMENT(songPipe), GST_STATE_PAUSED);

	return NULL;
}

void gst_init_player(const char *uri) {
	int ret = pthread_create(&songThread, NULL, startSongThread, (void*) uri);
	if (ret) {
		perror("thread\n");
	} else {
		puts("thread created.");
	}
}

void gst_pause_song(void) {
	gst_element_set_state(songPipe, GST_STATE_PAUSED);
}

void gst_resume_song(void) {
	gst_element_set_state(songPipe, GST_STATE_PLAYING);
	puts("resume function.");
}

void gst_play(void) {
	gst_element_set_state(songPipe, GST_STATE_PLAYING);
	//g_main_loop_run(songLoop);

	//gst_element_set_state(GST_ELEMENT(songPipe), GST_STATE_NULL);
	//gst_object_unref(GST_OBJECT(songPipe));
}

