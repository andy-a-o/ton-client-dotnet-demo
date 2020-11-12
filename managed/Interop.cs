﻿using System;
using System.Runtime.InteropServices;
using System.Text;

namespace test_dll_client
{
    internal static class Interop
    {
        private const string DllName = "testlib";

        /// <summary>
        /// Read string content provided by the <c>str</c>pointer.
        /// Returned value is the internal string data.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern test_string_data_t test_read_string(test_string_handle_t str);

        /// <summary>
        /// destroys rust string provided by <c>str</c> pointer.
        /// </summary>
        /// <param name="str"></param>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void test_destroy_string(test_string_handle_t str);

        /// <summary>
        /// 
        /// <p>Create context using provided <c>config</c> with configuration json.
        /// Returned string is a JSON with the result or the error.</p>
        ///
        /// <p>Result is returned in form of <c>{ "result": context }</c> where <c>context</c> is a number with context handle.
        /// Error is returned in form <c>{ "error": { error fields } }</c>.
        /// Note: <c>test_create_context</c> doesn't store pointer passed in config parameter.
        /// So it is safe to free this memory after the function returns.</p>
        /// 
        /// </summary>
        /// <param name="config"></param>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern test_string_handle_t test_create_context(test_string_data_t config);

        /// <summary>
        /// closes and releases all resources that was allocated and opened by library during serving functions related to provided context.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void test_destroy_context(uint context);

        /// <summary>
        /// Handles responses from the library.
        /// Note that an application can receive an unlimited count of responses related to single request.
        /// </summary>
        /// <param name="request_id">the request to which this response is addressed.</param>
        /// <param name="params_json">response parameters encoded into JSON string.</param>
        /// <param name="response_type"> type of this response:
        /// <c>RESULT = 0</c>, function result.
        /// <c>ERROR = 1</c>, function execution error.
        /// <c>NOP = 2</c>, no operation. In combination with <c>finished = true</c> signals that the request handling was finished.
        /// <c>RESERVED = 3..99</c> – reserved for protocol internal purposes. Application(or binding) must ignore this response. Nevertheless the binding must check the finished flag to release data, associated with request.
        /// <c>STREAM = 100..</c> - additional function data related to request handling. Depends on the function.</param>
        /// <param name="finished">is a signal to release all additional data associated with the request. It is last response for specified request_id.</param>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void test_response_handler_t(
            uint request_id,
            test_string_data_t params_json,
            uint response_type,
            bool finished);

        /// <summary>
        /// When application requires to invoke some ton client function it sends a function request to the library.
        /// </summary>
        /// <param name="context">Client internal context created in <see cref="test_create_context"></see></param>
        /// <param name="function_name">function name requested.</param>
        /// <param name="function_params_json">function parameters encoded as a JSON string. If a function hasn't parameters then en empty string must be passed.</param>
        /// <param name="request_id">application (or binding) defined request identifier. Usually binding allocates and stores some additional data with every request. This data will help in the future to properly route responses to the application.</param>
        /// <param name="response_handler">function that will receive responses related to this request.</param>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void test_request(
            uint context,
            test_string_data_t function_name,
            test_string_data_t function_params_json,
            uint request_id,
            [MarshalAs(UnmanagedType.FunctionPtr)]
            test_response_handler_t response_handler);

        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr test_request_sync(
            uint context,
            test_string_data_t function_name,
            test_string_data_t function_params_json);
    }

    [StructLayout(LayoutKind.Sequential)]
    internal class test_string_handle_t
    {
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct test_string_data_t
    {
        public IntPtr content;
        public UInt32 len;
    }

    enum test_response_types_t
    {
        test_response_success = 0,
        test_response_error = 1,
        test_response_nop = 2,
        test_response_custom = 100,
    }
}
