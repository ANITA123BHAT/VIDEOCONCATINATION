


//#include<gst/gst.h>
//
//
//int main(){
//	GstElement *pipeline, *videoconvert,*x264enc,*h264parse,*mp4mux,*filesink,*filesrc1,*filesrc2,*qtdemux1,*qtdemux2,*decodebin1,*decodebin2;
//	GstBus *bus;
//	GstMessage *msg;
//	gboolean terminate = FALSE;
//	//initialize gstreamer
//	gst_init(NULL,NULL);
//
//	//Create a pipelineand lemenet
//	pipeline=gst_pipeline_new("mypipeline");
//	videoconvert=gst_element_factory_make("videoconvert","videoconvert");
//	//videoscale=gst_element_factory_make("videscale","videoscale");
//	x264enc=gst_element_factory_make("x264enc","x264enc");
//	h264parse=gst_element_factory_make("h264parse","h264parse");
//	mp4mux=gst_element_factory_make("mp4mux","mp4mux");
//	filesink=gst_element_factory_make("filesink","filesink");
//	filesrc1=gst_element_factory_make("filesrc","filesrc1");
//	filesrc2=gst_element_factory_make("filesrc","filesrc2");
//	qtdemux1=gst_element_factory_make("qtdemux","qtdemux1");
//	qtdemux2=gst_element_factory_make("qtdemux","qtdemux2");
//	decodebin1=gst_element_factory_make("decodebin","decodebin1");
//	decodebin2=gst_element_factory_make("decodebin","decodebin2");
//	GstElement *concat = gst_element_factory_make("concat", "concat");
//
//	if(!pipeline || !videoconvert || !x264enc ||!h264parse || !mp4mux || !filesink || !filesrc1 || !filesrc2 || !qtdemux1 || !qtdemux2 || !decodebin1 || !decodebin2 || !concat){
//		g_print("Not all element could be created\n");
//		return -1;
//	}
//	//set the location for the source
//	g_object_set(filesrc1,"location","/home/ee212766/eclipse-workspace/videoconcatination/v1.mp4",NULL);
//	g_object_set(filesrc2,"location","/home/ee212766/eclipse-workspace/videoconcatination/v2.mp4",NULL);
//	g_object_set(filesink, "location", "bothmp4.mp4", NULL);
//	//add element to the pipiline
//	gst_bin_add_many(GST_BIN(pipeline),videoconvert,x264enc,h264parse,mp4mux,filesink,filesrc1,filesrc2,qtdemux1,qtdemux2,decodebin1,decodebin2,concat,NULL);
//
//	//link all element
//    if(!gst_element_link(filesrc1,qtdemux1)){
//    	g_printerr("Failed to link elements 1\n");
//    	       return -1;
//    }
//    /* Wait until pads are created and linked */
//        if (!gst_pad_link(gst_element_get_static_pad(qtdemux1, "video_0"), gst_element_get_static_pad(decodebin1, "sink"))) {
//            g_printerr("Failed to link demux1 to dec1 pads\n");
//            return -1;
//        }
//    if(!gst_element_link(qtdemux1,decodebin1)){
//    	g_printerr("Failed to link elements 2\n");
//    	    	       return -1;
//    }
//
//        if (!gst_pad_link(gst_element_get_static_pad(decodebin1, "video_0"), gst_element_get_static_pad(concat, "sink"))) {
//                   g_printerr("Failed to link decodebin to concat pads\n");
//                   return -1;
//               }
//    if(!gst_element_link(decodebin1,concat)){
//    	g_printerr("Failed to link elements 3\n");
//    	    	       return -1;
//    }
//    if(!gst_element_link(filesrc2,qtdemux2)){
//    	g_printerr("Failed to link elements 4\n");
//    	    	       return -1;
//    }
//
//    if (!gst_pad_link(gst_element_get_static_pad(qtdemux2, "video_%u"), gst_element_get_static_pad(decodebin2, "sink"))) {
//                g_printerr("Failed to link demux2 to dec2 pads\n");
//                return -1;
//        }
//    if(!gst_element_link(qtdemux2,decodebin2)){
//    	g_printerr("Failed to link elements 5\n");
//    	    	       return -1;
//    }
//    if (!gst_pad_link(gst_element_get_static_pad(decodebin2, "video_%u"), gst_element_get_static_pad(concat, "sink"))) {
//                      g_printerr("Failed to link decodebin2 to concat pads\n");
//                      return -1;
//                  }
//
//    if(!gst_element_link(decodebin2,concat)){
//    	g_printerr("Failed to link elements 6\n");
//    	    	       return -1;
//    }
//    if(!gst_element_link(concat,videoconvert)){
//    	g_printerr("Failed to link elements 7\n");
//    	    	    	       return -1;
//    }
////    if(!gst_element_link(videoconvert,videoscale)){
////    	g_printerr("Failed to link elements 8\n");
////    	    	    	       return -1;
////    }
//    if(!gst_element_link(videoconvert,x264enc)){
//    	g_printerr("Failed to link elements 9\n");
//    	    	    	       return -1;
//    }
//    if(!gst_element_link(x264enc,h264parse)){
//    	g_printerr("Failed to link elements 10\n");
//    	    	    	       return -1;
//    }
//    if(!gst_element_link(h264parse,mp4mux)){
//    	g_printerr("Failed to link elements 11\n");
//    	    	    	       return -1;
//    }
//    if(!gst_element_link(mp4mux,filesink)){
//    	g_printerr("Failed to link elements 12\n");
//    	    	    	       return -1;
//    }
//
//
//    // Start the pipeline
//     gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
//
//     // Wait until error or EOS
//      bus = gst_element_get_bus(GST_ELEMENT(pipeline));
//      do{
//      msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
//                                                   (GstMessageType)(GST_MESSAGE_ERROR |
//                                                   GST_MESSAGE_EOS));
//      if (msg != NULL) {
//    	  // Handle the message
//    	  GError *err;
//    	  gchar *debug_info;
//    	  switch (GST_MESSAGE_TYPE(msg)) {
//    	  case GST_MESSAGE_ERROR:
//    	  gst_message_parse_error(msg, &err, &debug_info);
//    	  g_printerr("Error received from element %s: %s\n",
//    	  GST_OBJECT_NAME(msg->src), err->message);
//    	  g_printerr("Debugging information: %s\n",
//    	  debug_info ? debug_info : "none");
//    	  g_error_free(err);
//    	  g_free(debug_info);
//    	  terminate = TRUE;
//    	  break;
//    	  case GST_MESSAGE_EOS:
//    	  g_print("End-Of-Stream reached.\n");
//    	  terminate = TRUE;
//    	  break;
//    	  default:
//    	  // Ignore other messages
//    	  break;
//    	  }
//    	  // Free the message
//    	  gst_message_unref(msg);
//      }
//      }while(!terminate);
//      // Stop the pipeline
//      gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
//
//      // Free resources
//      gst_object_unref(GST_OBJECT(pipeline));
//      gst_object_unref(GST_OBJECT(bus));
//      gst_deinit();
//
//      return 0;
//}

//
//
//
//#include<gst/gst.h>
//
//void on_mux1_decoder_pad_added (GstElement *qtdemux1, GstPad *pad, gpointer data) {
//	GstElement *decodebin1 = (GstElement *) data;
//	GstPad *sinkpad = gst_element_get_static_pad (decodebin1, "sink");
//	gst_pad_link (pad, sinkpad);
//	gst_object_unref (sinkpad);
//
//}
//void on_concat1_decoder_pad_added (GstElement *decodebin1, GstPad *pad, gpointer data) {
//	GstElement *concat = (GstElement *) data;
//	GstPad *sinkpad = gst_element_get_static_pad (concat, "sink");
//	gst_pad_link (pad, sinkpad);
//	gst_object_unref (sinkpad);
//}
//void on_mux2_decoder_pad_added (GstElement *qtdemux2, GstPad *pad, gpointer data) {
//	GstElement *decodebin2 = (GstElement *) data;
//	GstPad *sinkpad = gst_element_get_static_pad (decodebin2, "sink");
//	gst_pad_link (pad, sinkpad);
//	gst_object_unref (sinkpad);
//}
//void on_concat2_decoder_pad_added (GstElement *decodebin2, GstPad *pad, gpointer data) {
//	GstElement *concat = (GstElement *) data;
//	GstPad *sinkpad = gst_element_get_static_pad (concat, "sink");
//	gst_pad_link (pad, sinkpad);
//	gst_object_unref (sinkpad);
//}
//void on_mp4mux_pad_added (GstElement *mp4mux, GstPad *pad, gpointer data) {
//	GstElement *filesink = (GstElement *) data;
//	GstPad *sinkpad = gst_element_get_static_pad (filesink, "sink");
//	gst_pad_link (pad, sinkpad);
//	gst_object_unref (sinkpad);
//}
//
//int main(int argc,char *argv[]){
//	GstElement *pipeline, *videoconvert,*x264enc,*h264parse,*mp4mux,*filesink,*filesrc1,*filesrc2,*qtdemux1,*qtdemux2,*decodebin1,*decodebin2;
//	GstBus *bus;
//	GstMessage *msg;
//	gboolean terminate = FALSE;
//	//initialize gstreamer
//	gst_init(&argc,&argv);
//
//	//Create a pipelineand lemenet
//	pipeline=gst_pipeline_new("mypipeline");
//	videoconvert=gst_element_factory_make("videoconvert","videoconvert");
//	//videoscale=gst_element_factory_make("videscale","videoscale");
//	x264enc=gst_element_factory_make("x264enc","x264enc");
//	h264parse=gst_element_factory_make("h264parse","h264parse");
//	mp4mux=gst_element_factory_make("mp4mux","mp4mux");
//	filesink=gst_element_factory_make("filesink","filesink");
//	filesrc1=gst_element_factory_make("filesrc","filesrc1");
//	filesrc2=gst_element_factory_make("filesrc","filesrc2");
//	qtdemux1=gst_element_factory_make("qtdemux","qtdemux1");
//	qtdemux2=gst_element_factory_make("qtdemux","qtdemux2");
//	decodebin1=gst_element_factory_make("decodebin","decodebin1");
//	decodebin2=gst_element_factory_make("decodebin","decodebin2");
//	GstElement *concat = gst_element_factory_make("concat", "concat");
//
//	if(!pipeline || !videoconvert || !x264enc ||!h264parse || !mp4mux || !filesink || !filesrc1 || !filesrc2 || !qtdemux1 || !qtdemux2 || !decodebin1 || !decodebin2 || !concat){
//		g_print("Not all element could be created\n");
//		return -1;
//	}
//	//set the location for the source
//	g_object_set(filesrc1,"location","/home/ee212766/eclipse-workspace/videoconcatination/v1.mp4",NULL);
//	g_object_set(filesrc2,"location","/home/ee212766/eclipse-workspace/videoconcatination/v2.mp4",NULL);
//	g_object_set(filesink, "location", "bothmp4.mp4", NULL);
//	//add element to the pipiline
//	gst_bin_add_many(GST_BIN(pipeline),videoconvert,x264enc,h264parse,mp4mux,filesink,filesrc1,filesrc2,qtdemux1,qtdemux2,decodebin1,decodebin2,concat,NULL);
//
//	//link all element
//    if(!gst_element_link(filesrc1,qtdemux1)){
//    	g_printerr("Failed to link elements 1\n");
//    	       return -1;
//    }
//    g_signal_connect(qtdemux1, "pad-added", G_CALLBACK(on_mux1_decoder_pad_added),decodebin1);
//    if(!gst_element_link(qtdemux1,decodebin1)){
//    	g_printerr("Failed to link elements 2\n");
//    	    	       return -1;
//    }
//    g_signal_connect(decodebin1, "pad-added", G_CALLBACK(on_concat1_decoder_pad_added),concat);
//    if(!gst_element_link(decodebin1,concat)){
//        	g_printerr("Failed to link elements 3\n");
//        	    	       return -1;
//        }
//    if(!gst_element_link(filesrc2,qtdemux2)){
//    	g_printerr("Failed to link elements 4\n");
//    	    	       return -1;
//    }
//    g_signal_connect(qtdemux2, "pad-added", G_CALLBACK(on_mux2_decoder_pad_added),decodebin2);
//    if(!gst_element_link(qtdemux2,decodebin2)){
//    	g_printerr("Failed to link elements 5\n");
//    	    	       return -1;
//    }
//
//    g_signal_connect(decodebin2, "pad-added", G_CALLBACK(on_concat2_decoder_pad_added),concat);
//    if(!gst_element_link(decodebin2,concat)){
//    	g_printerr("Failed to link elements 6\n");
//    	    	       return -1;
//    }
//
//    if(!gst_element_link(concat,videoconvert)){
//    	g_printerr("Failed to link elements 7\n");
//    	    	    	       return -1;
//    }
////    if(!gst_element_link(videoconvert,videoscale)){
////    	g_printerr("Failed to link elements 8\n");
////    	    	    	       return -1;
////    }
//
//    if(!gst_element_link(videoconvert,x264enc)){
//    	g_printerr("Failed to link elements 9\n");
//    	    	    	       return -1;
//    }
//    if(!gst_element_link(x264enc,h264parse)){
//    	g_printerr("Failed to link elements 10\n");
//    	    	    	       return -1;
//    }
//
//    if(!gst_element_link(h264parse,mp4mux)){
//    	g_printerr("Failed to link elements 11\n");
//    	    	    	       return -1;
//    }
//    g_signal_connect(mp4mux, "pad-added", G_CALLBACK(on_mp4mux_pad_added),filesink);
//    if(!gst_element_link(mp4mux,filesink)){
//    	g_printerr("Failed to link elements 12\n");
//    	    	    	       return -1;
//    }
//
//
//    // Start the pipeline
//     gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
//
//     // Wait until error or EOS
//      bus = gst_element_get_bus(GST_ELEMENT(pipeline));
//      do{
//      msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
//                                                   (GstMessageType)(GST_MESSAGE_ERROR |
//                                                   GST_MESSAGE_EOS));
//      if (msg != NULL) {
//    	  // Handle the message
//    	  GError *err;
//    	  gchar *debug_info;
//    	  switch (GST_MESSAGE_TYPE(msg)) {
//    	  case GST_MESSAGE_ERROR:
//    	  gst_message_parse_error(msg, &err, &debug_info);
//    	  g_printerr("Error received from element %s: %s\n",
//    	  GST_OBJECT_NAME(msg->src), err->message);
//    	  g_printerr("Debugging information: %s\n",
//    	  debug_info ? debug_info : "none");
//    	  g_error_free(err);
//    	  g_free(debug_info);
//    	  terminate = TRUE;
//    	  break;
//    	  case GST_MESSAGE_EOS:
//    	  g_print("End-Of-Stream reached.\n");
//    	  terminate = TRUE;
//    	  break;
//    	  default:
//    	  // Ignore other messages
//    	  break;
//    	  }
//    	  // Free the message
//    	  gst_message_unref(msg);
//      }
//      }while(!terminate);
//      // Stop the pipeline
//      gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
//
//      // Free resources
//      gst_object_unref(GST_OBJECT(pipeline));
//      gst_object_unref(GST_OBJECT(bus));
//      gst_deinit();
//
//      return 0;
//}



//
//#include <gst/gst.h>
//
//void on_mux1_decoder_pad_added (GstElement *qtdemux1, GstPad *pad, gpointer data) {
//	GstElement *decodebin1 = (GstElement *) data;
//	GstPad *sinkpad = gst_element_get_static_pad (decodebin1, "sink");
//	gst_pad_link (pad, sinkpad);
//	gst_object_unref (sinkpad);
//}
//
//int main(int argc, char *argv[]) {
//    GstElement *pipeline, *c, *videoconvert, *x264enc, *h264parse, *mp4mux, *filesink, *filesrc1, *filesrc2, *qtdemux1, *qtdemux2, *decodebin1, *decodebin2;
//    GMainLoop *loop;
//    GstStateChangeReturn ret;
//
//    /* Initialize GStreamer */
//    gst_init(&argc, &argv);
//    loop = g_main_loop_new(NULL, FALSE);
//
//    /* Create elements */
//    pipeline = gst_pipeline_new("concat_pipeline");
//    c = gst_element_factory_make("concat", "c");
//    videoconvert = gst_element_factory_make("videoconvert", NULL);
//    x264enc = gst_element_factory_make("x264enc", NULL);
//    h264parse = gst_element_factory_make("h264parse", NULL);
//    mp4mux = gst_element_factory_make("mp4mux", NULL);
//    filesink = gst_element_factory_make("filesink", NULL);
//    filesrc1 = gst_element_factory_make("filesrc", NULL);
//    filesrc2 = gst_element_factory_make("filesrc", NULL);
//    qtdemux1 = gst_element_factory_make("qtdemux", "de");
//    qtdemux2 = gst_element_factory_make("qtdemux", "dec");
//    decodebin1 = gst_element_factory_make("decodebin", NULL);
//    decodebin2 = gst_element_factory_make("decodebin", NULL);
//
//    /* Check that all elements were created */
//    if (!pipeline || !c || !videoconvert || !x264enc || !h264parse || !mp4mux || !filesink || !filesrc1 || !filesrc2 || !qtdemux1 || !qtdemux2 || !decodebin1 || !decodebin2) {
//        g_printerr("Not all elements could be created.\n");
//        return -1;
//    }
//
//    /* Set properties for elements */
//    g_object_set(G_OBJECT(filesink), "location", "output.mp4", NULL);
//    g_object_set(G_OBJECT(filesrc1), "location", "/home/ee212766/eclipse-workspace/videoconcatination/v1.mp4", NULL);
//    g_object_set(G_OBJECT(filesrc2), "location", "/home/ee212766/eclipse-workspace/videoconcatination/v2.mp4", NULL);
//
//
//    /* Add elements to pipeline */
//    gst_bin_add_many(GST_BIN(pipeline), filesrc1, qtdemux1, decodebin1, c, NULL);
//    gst_bin_add_many(GST_BIN(pipeline), filesrc2, qtdemux2, decodebin2, NULL);
//    gst_bin_add_many(GST_BIN(pipeline), videoconvert, x264enc, h264parse, mp4mux, filesink, NULL);
//    /* Link elements */
//    g_signal_connect(qtdemux1, "pad-added", G_CALLBACK(on_mux1_decoder_pad_added),decodebin1);
//    if (!gst_element_link_many(filesrc1, qtdemux1,NULL)){
//    	g_printerr("Failed to link elements 1.\n");
//    	        return -1;
//    }
//    if(!gst_element_link(qtdemux1,decodebin1)){
//    	g_printerr("Failed to link elements 2.\n");
//    	    	        return -1;
//    }
//    	if(gst_element_link_many(decodebin1, c, NULL) ){
//    		g_printerr("Failed to link elements 3.\n");
//    		        return -1;
//    	}
//
//    	if (!gst_element_link_many(filesrc2, qtdemux2,NULL)){
//    	    	g_printerr("Failed to link elements 1.\n");
//    	    	        return -1;
//    	    }
//    	    if(!gst_element_link_many(qtdemux2,decodebin2,NULL)){
//    	    	g_printerr("Failed to link elements 2.\n");
//    	    	    	        return -1;
//    	    }
//    	    	if(gst_element_link_many(decodebin2, c, NULL) ){
//    	    		g_printerr("Failed to link elements 3.\n");
//    	    		        return -1;
//    	    	}
//
////    if (!gst_element_link_many(filesrc2, qtdemux2, decodebin2, c, NULL)) {
////        g_printerr("Failed to link elements 2.\n");
////        return -1;
////    }
//    if (!gst_element_link_many(c, videoconvert, x264enc, h264parse, mp4mux, filesink, NULL)) {
//        g_printerr("Failed to link elements 3.\n");
//        return -1;
//    }
//
//    /* Set the pipeline to the "playing" state */
//    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
//    if (ret == GST_STATE_CHANGE_FAILURE) {
//        g_printerr("Failed to set pipeline to playing state.\n");
//        return -1;
//    }
//
//    /* Wait until error or EOS */
//    g_print("Running...\n");
//    g_main_loop_run(loop);
//
//    /* Clean up */
//    g_print("Returned, stopping playback\n");
//    gst_element_set_state(pipeline, GST_STATE_NULL);
//    g_print("Deleting pipeline\n");
//    gst_object_unref(GST_OBJECT(pipeline));
//    g_main_loop_unref(loop);
//
//    return 0;
//}

//Command for videoconcatination.
//gst-launch-1.0 concat name=c ! videoconvert ! videoscale ! x264enc ! h264parse ! mp4mux ! filesink location=bothmp4.mp4 filesrc location=bahubali1.mp4 ! qtdemux name=de de.video_0 ! decodebin ! c. filesrc location=bahubali.mp4 ! qtdemux name=dec dec.video_0 ! decodebin ! c.


#include <gst/gst.h>

/* Structure to contain all our information, so we can pass it to callbacks */
typedef struct _CustomData {
  GstElement *pipeline;
  GstElement *source1;
  GstElement *source2;
  GstElement *vconvert1;
  GstElement *vconvert2;
  GstElement *aconvert1;
  GstElement *aconvert2;
  GstElement *concat;
  GstElement *mp4mux;
  GstElement *x264enc;
  GstElement *h264parse;
  GstElement *qtdemux1;
  GstElement *qtdemux2;
  GstElement *decodebin1;
  GstElement *decodebin2;
  GstElement *filesink;
} CustomData;

/* Handler for the pad-added signal */
static void pad_added_handler (GstElement *src, GstPad *pad, CustomData *data);
static void pad_added_handler1(GstElement *src, GstPad *pad, CustomData *data);
static void pad_added_handler2 (GstElement *src, GstPad *pad, CustomData *data);
static void pad_added_handler3 (GstElement *src, GstPad *pad, CustomData *data);
static void pad_added_handler4 (GstElement *src, GstPad *pad, CustomData *data);
static void pad_added_handler5 (GstElement *src, GstPad *pad, CustomData *data);
int main() {
  CustomData data;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  gboolean terminate = FALSE;

  /* Initialize GStreamer */
  gst_init (NULL,NULL);


  	data.vconvert1=gst_element_factory_make("videoconvert","vconvert1");
  	data.vconvert2=gst_element_factory_make("videoconvert","vconvert2");
  	data.aconvert1=gst_element_factory_make("audioconvert","aconvert1");
  	data.aconvert2=gst_element_factory_make("audioconvert","aconvert2");
  	//videoscale=gst_element_factory_make("videscale","videoscale");
  	data.x264enc=gst_element_factory_make("x264enc","x264enc");
  	data.h264parse=gst_element_factory_make("h264parse","h264parse");
  	data.mp4mux=gst_element_factory_make("mp4mux","mp4mux");
  	data.filesink=gst_element_factory_make("filesink","filesink");
  	data.source1=gst_element_factory_make("filesrc","source1");
  	data.source2=gst_element_factory_make("filesrc","source22");
  	data.qtdemux1=gst_element_factory_make("qtdemux","qtdemux1");
  	data.qtdemux2=gst_element_factory_make("qtdemux","qtdemux2");
  	data.decodebin1=gst_element_factory_make("decodebin","decodebin1");
  	data.decodebin2=gst_element_factory_make("decodebin","decodebin2");
    data.concat = gst_element_factory_make("concat", "concat");

  /* Create the empty pipeline */
  data.pipeline = gst_pipeline_new ("mypipeline");

  if(!data.pipeline || !data.vconvert1 || !data.vconvert2 || !data.aconvert1 || !data.aconvert2 || !data.x264enc ||!data.h264parse || !data.mp4mux || !data.filesink || !data.source1 || !data.source2 || !data.qtdemux1 || !data.qtdemux2 || !data.decodebin1 || !data.decodebin2 || !data.concat){
  		g_print("Not all element could be created\n");
  		return -1;
  	}


  /* Set properties for elements */
      g_object_set(G_OBJECT(data.filesink), "location", "output.mp4", NULL);
      g_object_set(G_OBJECT(data.source1), "location", "/home/ee212766/eclipse-workspace/videoconcatination/v1.mp4", NULL);
      g_object_set(G_OBJECT(data.source2), "location", "/home/ee212766/eclipse-workspace/videoconcatination/v2.mp4", NULL);

  /* Build the pipeline. Note that we are NOT linking the source at this
   * point. We will do it later. */
      gst_bin_add_many(GST_BIN(data.pipeline),data.vconvert1,data.vconvert2,data.aconvert1, data.aconvert2, data.x264enc,data.h264parse,data.mp4mux,data.filesink,data.source1,data.source2,data.qtdemux1,data.qtdemux2,data.decodebin1,data.decodebin2,data.concat,NULL);


      //link all element
          if(!gst_element_link(data.source1,data.qtdemux1)){
          	g_printerr("Failed to link elements 1\n");
          	       return -1;
          }
          g_signal_connect(data.qtdemux1, "pad-added", G_CALLBACK(pad_added_handler1),&data);

          g_signal_connect(data.decodebin1, "pad-added", G_CALLBACK(pad_added_handler),&data);
          g_signal_connect(data.decodebin1,"pad-added",G_CALLBACK(pad_added_handler4),&data);

//          if(!gst_element_link(data.decodebin1,data.vconvert1)){
//              	g_printerr("Failed to link elements 3\n");
//              	    	       return -1;
//              }
          /*..........decodebin1 to aconvert1...*/


          if(!gst_element_link(data.vconvert1,data.concat)){
                            	g_printerr("Failed to link elements 2\n");
                            	    	    	       return -1;
                            }
//
//          if(!gst_element_link(data.aconvert1,data.concat)){
//                                     	g_printerr("Failed to link elements 3\n");
//                                     	    	    	       return -1;
//                                     }

          if(!gst_element_link(data.source2,data.qtdemux2)){
          	g_printerr("Failed to link elements 4\n");
          	    	       return -1;
          }
          g_signal_connect(data.qtdemux2, "pad-added", G_CALLBACK(pad_added_handler3),&data);

//          if(!gst_element_link(data.qtdemux2,data.decodebin2)){
//          	g_printerr("Failed to link elements 5\n");
//          	    	       return -1;
//          }



          g_signal_connect(data.decodebin2, "pad-added", G_CALLBACK(pad_added_handler2),&data);
          g_signal_connect(data.decodebin2,"pad-added",G_CALLBACK(pad_added_handler5),&data);
//          if(!gst_element_link(data.decodebin2,data.vconvert2)){
//          	g_printerr("Failed to link elements 6\n");
//          	    	       return -1;
//          }

          if(!gst_element_link(data.vconvert2,data.concat)){
                                      	g_printerr("Failed to link elements 8\n");
                                      	    	    	       return -1;
                                      }
//
//          if(!gst_element_link(data.aconvert2,data.concat)){
//                                               	g_printerr("Failed to link elements 13\n");
//                                               	    	    	       return -1;
//                                               }

          if(!gst_element_link(data.concat,data.x264enc)){
          	g_printerr("Failed to link elements 9\n");
          	    	    	       return -1;
          }

          if(!gst_element_link(data.x264enc,data.h264parse)){
          	g_printerr("Failed to link elements 10\n");
          	    	    	       return -1;
          }

          if(!gst_element_link(data.h264parse,data.mp4mux)){
          	g_printerr("Failed to link elements 11\n");
          	    	    	       return -1;
          }

          if(!gst_element_link(data.mp4mux,data.filesink)){
          	g_printerr("Failed to link elements 12\n");
          	    	    	       return -1;
          }



  /* Connect to the pad-added signal */
  //g_signal_connect (data.source1, "pad-added", G_CALLBACK (pad_added_handler), &data);

  /* Start playing */
  ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data.pipeline);
    return -1;
  }

  /* Listen to the bus */
  bus = gst_element_get_bus (data.pipeline);
  do {
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
        (GstMessageType)(GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;

      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = TRUE;
          break;
        case GST_MESSAGE_EOS:
          g_print ("End-Of-Stream reached.\n");
          terminate = TRUE;
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
        default:
          /* We should not reach here */
          g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
  } while (!terminate);

  /* Free resources */
  gst_object_unref (bus);
  gst_element_set_state (data.pipeline, GST_STATE_NULL);
  gst_object_unref (data.pipeline);
  return 0;
}

/* This function will be called by the pad-added signal */
static void pad_added_handler (GstElement *src, GstPad *new_pad, CustomData *data) {
	//GstElement * sink= (GstElement *) data;
  GstPad *sink_pad = gst_element_get_static_pad (data->vconvert1, "sink");

  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("We are already linked. Ignoring.\n");
    goto exit;
  }

  /* Check the new pad's type */
  new_pad_caps = gst_pad_get_current_caps (new_pad);
  new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
  new_pad_type = gst_structure_get_name (new_pad_struct);
  if (!g_str_has_prefix (new_pad_type, "video/x-raw")) {
    g_print ("It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
    goto exit;
  }

  /* Attempt the link */
  ret = gst_pad_link (new_pad, sink_pad);
  if (GST_PAD_LINK_FAILED (ret)) {
    g_print ("Type is '%s' but link failed.\n", new_pad_type);
  } else {
    g_print ("Link succeeded (type '%s').\n", new_pad_type);
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}


/* This function will be called by the pad-added signal */
static void pad_added_handler2 (GstElement *src, GstPad *new_pad, CustomData *data) {
	//GstElement * sink= (GstElement *) data;
  GstPad *sink_pad = gst_element_get_static_pad (data->vconvert2, "sink");
  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;
  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("We are already linked. Ignoring.\n");
    goto exit;
  }

  /* Check the new pad's type */
  new_pad_caps = gst_pad_get_current_caps (new_pad);
  new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
  new_pad_type = gst_structure_get_name (new_pad_struct);
  if (!g_str_has_prefix (new_pad_type, "video/x-raw")) {
    g_print ("It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
    goto exit;
  }

  /* Attempt the link */
  ret = gst_pad_link (new_pad, sink_pad);
  if (GST_PAD_LINK_FAILED (ret)) {
    g_print ("Type is '%s' but link failed.\n", new_pad_type);
  } else {
    g_print ("Link succeeded (type '%s').\n", new_pad_type);
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}



static void pad_added_handler1 (GstElement *src, GstPad *new_pad, CustomData *data) {
	//GstElement * sink= (GstElement *) data;
  GstPad *sink_pad = gst_element_get_static_pad (data->decodebin1, "sink");
  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  //GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("We are already linked. Ignoring.\n");
    goto exit;
  }



  /* Attempt the link */
  ret = gst_pad_link (new_pad, sink_pad);
  if (GST_PAD_LINK_FAILED (ret)) {
    g_print ("Type is '%s' but link failed.\n", new_pad_type);
  } else {
    g_print ("Link succeeded (type '%s').\n", new_pad_type);
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}

static void pad_added_handler3 (GstElement *src, GstPad *new_pad, CustomData *data) {
	//GstElement * sink= (GstElement *) data;
  GstPad *sink_pad = gst_element_get_static_pad (data->decodebin2, "sink");
  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  //GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("We are already linked. Ignoring.\n");
    goto exit;
  }



  /* Attempt the link */
  ret = gst_pad_link (new_pad, sink_pad);
  if (GST_PAD_LINK_FAILED (ret)) {
    g_print ("Type is '%s' but link failed.\n", new_pad_type);
  } else {
    g_print ("Link succeeded (type '%s').\n", new_pad_type);
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}

static void pad_added_handler4(GstElement *src, GstPad *new_pad, CustomData *data) {
	//GstElement * sink= (GstElement *) data;
  GstPad *sink_pad = gst_element_get_static_pad (data->aconvert1, "sink");

  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("We are already linked. Ignoring.\n");
    goto exit;
  }

  /* Check the new pad's type */
  new_pad_caps = gst_pad_get_current_caps (new_pad);
  new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
  new_pad_type = gst_structure_get_name (new_pad_struct);
  if (!g_str_has_prefix (new_pad_type, "audio/x-raw")) {
    g_print ("It has type '%s' which is not raw video. Ignoring.\n", new_pad_type);
    goto exit;
  }

  /* Attempt the link */
  ret = gst_pad_link (new_pad, sink_pad);
  if (GST_PAD_LINK_FAILED (ret)) {
    g_print ("Type is '%s' but link failed.\n", new_pad_type);
  } else {
    g_print ("Link succeeded (type '%s').\n", new_pad_type);
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}

static void pad_added_handler5(GstElement *src, GstPad *new_pad, CustomData *data) {
	//GstElement * sink= (GstElement *) data;
  GstPad *sink_pad = gst_element_get_static_pad (data->aconvert2, "sink");

  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("We are already linked. Ignoring.\n");
    goto exit;
  }

  /* Check the new pad's type */
  new_pad_caps = gst_pad_get_current_caps (new_pad);
  new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
  new_pad_type = gst_structure_get_name (new_pad_struct);
  if (!g_str_has_prefix (new_pad_type, "audio/x-raw")) {
    g_print ("It has type '%s' which is not raw video. Ignoring.\n", new_pad_type);
    goto exit;
  }

  /* Attempt the link */
  ret = gst_pad_link (new_pad, sink_pad);
  if (GST_PAD_LINK_FAILED (ret)) {
    g_print ("Type is '%s' but link failed.\n", new_pad_type);
  } else {
    g_print ("Link succeeded (type '%s').\n", new_pad_type);
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);
  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}


