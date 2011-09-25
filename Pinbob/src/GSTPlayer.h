/*
 * GSTPlayer.h
 *
 *  Created on: Sep 24, 2011
 *      Author: yejiabin
 */

#ifndef GSTPLAYER_H_
#define GSTPLAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

extern void gst_init_player(const char *uri);
extern void gst_play(void);
extern void gst_pause_song(void);
extern void gst_resume_song(void);
extern void gst_destroy(void);

#ifdef __cplusplus
};
#endif

#endif /* GSTPLAYER_H_ */
