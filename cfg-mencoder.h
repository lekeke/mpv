/*
 * config for cfgparser
 */

#include "cfg-common.h"

#ifdef USE_FAKE_MONO
extern int fakemono; // defined in dec_audio.c
#endif
#ifdef HAVE_ODIVX_POSTPROCESS
extern int use_old_pp;
#endif

extern int sws_flags;

#ifdef HAVE_DIVX4ENCORE
struct config divx4opts_conf[]={
	{"br", &divx4_param.bitrate, CONF_TYPE_INT, CONF_RANGE, 4, 24000000},
	{"rc_period", &divx4_param.rc_period, CONF_TYPE_INT, 0,0,0},
	{"rc_reaction_period", &divx4_param.rc_reaction_period, CONF_TYPE_INT, 0,0,0},
	{"rc_reaction_ratio", &divx4_param.rc_reaction_ratio, CONF_TYPE_INT, 0,0,0},
	{"min_quant", &divx4_param.min_quantizer, CONF_TYPE_INT, CONF_RANGE,0,32},
	{"max_quant", &divx4_param.max_quantizer, CONF_TYPE_INT, CONF_RANGE,0,32},
	{"key", &divx4_param.max_key_interval, CONF_TYPE_INT, CONF_MIN,0,0},
	{"deinterlace", &divx4_param.deinterlace, CONF_TYPE_FLAG, 0,0,1},
	{"q", &divx4_param.quality, CONF_TYPE_INT, CONF_RANGE, 1, 5},
	{"crispness", &divx4_crispness, CONF_TYPE_INT, CONF_RANGE,0,100},
	{"help", "TODO: divx4opts help!\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
	{NULL, NULL, 0, 0, 0, 0}
};
#endif

#ifdef HAVE_MP3LAME
struct config lameopts_conf[]={
	{"q", &lame_param_quality, CONF_TYPE_INT, CONF_RANGE, 0, 9},
	{"vbr", &lame_param_vbr, CONF_TYPE_INT, CONF_RANGE, 0, vbr_max_indicator},
	{"cbr", &lame_param_vbr, CONF_TYPE_FLAG, 0, 0, 0},
	{"abr", &lame_param_vbr, CONF_TYPE_FLAG, 0, 0, vbr_abr},
	{"mode", &lame_param_mode, CONF_TYPE_INT, CONF_RANGE, 0, MAX_INDICATOR},
	{"padding", &lame_param_padding, CONF_TYPE_INT, CONF_RANGE, 0, PAD_MAX_INDICATOR},
	{"br", &lame_param_br, CONF_TYPE_INT, CONF_RANGE, 0, 1024},
	{"ratio", &lame_param_ratio, CONF_TYPE_INT, CONF_RANGE, 0, 100},
	{"help", "TODO: lameopts help!\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
	{NULL, NULL, 0, 0, 0, 0}
};
#endif

#ifdef USE_LIBAVCODEC
struct config lavcopts_conf[]={
	{"vcodec", &lavc_param_vcodec, CONF_TYPE_STRING, 0, 0, 0},
	{"vbitrate", &lavc_param_vbitrate, CONF_TYPE_INT, CONF_RANGE, 4, 24000000},
	{"vhq", &lavc_param_vhq, CONF_TYPE_FLAG, 0, 0, 1},
	{"keyint", &lavc_param_keyint, CONF_TYPE_INT, 0, 0, 0},
	{NULL, NULL, 0, 0, 0, 0}
};
#endif

#ifdef USE_WIN32DLL
struct config vfwopts_conf[]={
	{NULL, NULL, 0, 0, 0, 0}
};
#endif

struct config ovc_conf[]={
	{"copy", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_COPY},
	{"frameno", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_FRAMENO},
	{"divx4", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_DIVX4},
	{"raw", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_RAW},
	{"lavc", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_LIBAVCODEC},
	{"help", "\nAvailable codecs:\n   copy\n   frameno\n   divx4\n   raw\n   lavc\n\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
	{NULL, NULL, 0, 0, 0, 0}
};

struct config oac_conf[]={
	{"copy", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_COPY},
	{"pcm", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_PCM},
#ifdef HAVE_MP3LAME
	{"mp3lame", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_VBRMP3},
	{"help", "\nAvailable codecs:\n   copy\n   pcm\n   mp3lame\n\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
#else
	{"mp3lame", "MPlayer was compiled without libmp3lame support!\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
	{"help", "\nAvailable codecs:\n   copy\n   pcm\n\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
#endif
	{NULL, NULL, 0, 0, 0, 0}
};

struct config conf[]={
	/* name, pointer, type, flags, min, max */
	{"include", cfg_include, CONF_TYPE_FUNC_PARAM, 0, 0, 0}, /* this must be the first!!! */

	{"ofps", &force_ofps, CONF_TYPE_FLOAT, CONF_MIN, 0, 0},
	{"o", &out_filename, CONF_TYPE_STRING, 0, 0, 0},

	{"x", &vo_w, CONF_TYPE_INT, CONF_RANGE, 0, 4096},
	{"y", &vo_h, CONF_TYPE_INT, CONF_RANGE, 0, 4096},

	{"mp3file", &mp3_filename, CONF_TYPE_STRING, 0, 0, 0},
	{"ac3file", &ac3_filename, CONF_TYPE_STRING, 0, 0, 0},

//	{"oac", &out_audio_codec, CONF_TYPE_STRING, 0, 0, 0},
//	{"ovc", &out_video_codec, CONF_TYPE_STRING, 0, 0, 0},
	{"oac", oac_conf, CONF_TYPE_SUBCONFIG, 0, 0, 0},
	{"ovc", ovc_conf, CONF_TYPE_SUBCONFIG, 0, 0, 0},

	{"ffourcc", &force_fourcc, CONF_TYPE_STRING, 0, 4, 4},

#ifdef HAVE_DIVX4ENCORE
	{"pass", &pass, CONF_TYPE_INT, CONF_RANGE,0,2},
	{"passlogfile", &passtmpfile, CONF_TYPE_STRING, 0, 0, 0},
	
	{"divx4opts", divx4opts_conf, CONF_TYPE_SUBCONFIG, 0, 0, 0},
#endif
#ifdef HAVE_MP3LAME
	{"lameopts", lameopts_conf, CONF_TYPE_SUBCONFIG, 0, 0, 0},
#endif
#ifdef USE_LIBAVCODEC
	{"lavcopts", lavcopts_conf, CONF_TYPE_SUBCONFIG, 0, 0, 0},
#endif
#ifdef USE_WIN32DLL
	{"vfwopts", vfwopts_conf, CONF_TYPE_SUBCONFIG, 0, 0, 0},
#endif

#define MAIN_CONF
#include "cfg-common.h"
#undef MAIN_CONF

//	{"quiet", &quiet, CONF_TYPE_FLAG, 0, 0, 1},
	{"verbose", &verbose, CONF_TYPE_INT, CONF_RANGE, 0, 100},
	{"v", cfg_inc_verbose, CONF_TYPE_FUNC, 0, 0, 0},
//	{"-help", help_text, CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
//	{"help", help_text, CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
//	{"h", help_text, CONF_TYPE_PRINT, CONF_NOCFG, 0, 0},
	{NULL, NULL, 0, 0, 0, 0}
};
