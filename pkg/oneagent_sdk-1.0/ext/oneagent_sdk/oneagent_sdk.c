#include <ruby.h>
#include "include/onesdk.h"

/*VALUE onesdk_initialize(VALUE self);
VALUE onesdk_incomingremotecalltracer_create(VALUE self, VALUE serviceMethod, VALUE serviceName, VALUE serviceEndpoint);
VALUE onesdk_tracer_start(VALUE self, VALUE tracer);
VALUE onesdk_tracer_end(VALUE self, VALUE tracer);
VALUE onesdk_shutdown(VALUE self);
VALUE onesdk_databaseinfo_create(VALUE self, VALUE dbname, VALUE dbtype, VALUE channeltype, VALUE endpoint);
VALUE onesdk_databaserequesttracer_create_sql(VALUE self, VALUE m_db_info_handle, VALUE sql);
*/
static VALUE oneagent_sdk_initialize(VALUE self) {
	return INT2NUM(onesdk_initialize());
}

static VALUE oneagent_sdk_get_version_string(VALUE self) {
	return rb_str_new(onesdk_agent_get_version_string(), strlen(onesdk_agent_get_version_string()));
}

static VALUE oneagent_sdk_incomingremotecalltracer_create(VALUE self, VALUE serviceMethod, VALUE serviceName, VALUE serviceEndpoint) {
        onesdk_tracer_handle_t const tracer = onesdk_incomingremotecalltracer_create(onesdk_asciistr(StringValueCStr(serviceMethod)),onesdk_asciistr(StringValueCStr(serviceName)), onesdk_asciistr(StringValueCStr(serviceEndpoint)));
        return ULONG2NUM(tracer);
}   

static VALUE oneagent_sdk_tracer_start(VALUE self, VALUE tracer) {
        onesdk_tracer_start((onesdk_tracer_handle_t) NUM2ULONG(tracer));
        return UINT2NUM(1);
}

static VALUE oneagent_sdk_tracer_end(VALUE self, VALUE tracer) {
        onesdk_tracer_end((onesdk_tracer_handle_t) NUM2ULONG(tracer));
        return UINT2NUM(1);
}

static VALUE oneagent_sdk_shutdown(VALUE self) {
        onesdk_shutdown();
        return UINT2NUM(1);
}

static VALUE oneagent_sdk_databaseinfo_create(VALUE self, VALUE dbname, VALUE dbtype, VALUE channeltype, VALUE endpoint) {
        onesdk_databaseinfo_handle_t m_db_info_handle = onesdk_databaseinfo_create(onesdk_asciistr("sample-config.db"),onesdk_asciistr("sqlite"), ONESDK_CHANNEL_TYPE_IN_PROCESS, onesdk_nullstr());
        return ULONG2NUM(m_db_info_handle);
}

static VALUE oneagent_sdk_databaserequesttracer_create_sql(VALUE self, VALUE m_db_info_handle, VALUE sql) {
        onesdk_tracer_handle_t const tracer = onesdk_databaserequesttracer_create_sql((onesdk_databaseinfo_handle_t) NUM2ULONG(m_db_info_handle), onesdk_str(StringValueCStr(sql), strlen(StringValueCStr(sql)), ONESDK_CCSID_ASCII));
        onesdk_tracer_start(tracer);
        onesdk_tracer_end(tracer);
        return UINT2NUM(1);
}

void Init_oneagent_sdk(void) {
	VALUE module;

	module = rb_const_get(rb_cObject, rb_intern("OneAgentSdk"));
	rb_define_module_function(module, "initialize", oneagent_sdk_initialize, 0);
	rb_define_module_function(module, "getVersion", oneagent_sdk_get_version_string, 0);
	rb_define_module_function(module, "incomingremotecalltracer_create", oneagent_sdk_incomingremotecalltracer_create, 3);
	rb_define_module_function(module, "tracer_start", oneagent_sdk_tracer_start, 1);
	rb_define_module_function(module, "tracer_end", oneagent_sdk_tracer_end, 1);
	rb_define_module_function(module, "shutdown", oneagent_sdk_shutdown, 0);
	rb_define_module_function(module, "databaseinfo_create", oneagent_sdk_databaseinfo_create, 4);
	rb_define_module_function(module, "databaserequesttracer_create_sql", oneagent_sdk_databaserequesttracer_create_sql, 2);
}

/*

how to build this stuff (currently works on linux 64 bit ONLY

navigate into the folder 'oneagent_sdk'

rake repackage
sudo gem install pkg/oneagent_sdk-1.0.gem

*/

/*

examples

irb
require 'oneagent_sdk'
OneAgentSdk.initialize
OneAgentSdk.getVersion

*/

