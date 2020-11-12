using System;
using System.Runtime.InteropServices;
using System.Text;

namespace test_dll_client
{
    class Program
    {
        static void Main(string[] args)
        {
            var intPtr = Interop.test_create_context(ToTonString("{}"));
            Interop.test_read_string(intPtr);
            Interop.test_destroy_string(intPtr);
        }

        private static test_string_data_t ToTonString(string str)
        {
            var bytes = Encoding.UTF8.GetBytes(str);
            var length = bytes.Length;
            var result = new test_string_data_t { content = Marshal.AllocHGlobal(length) };
            Marshal.Copy(bytes, 0, result.content, length);
            result.len = (uint)length;
            return result;
        }

        public static string FromTonString(test_string_data_t str)
        {
            var bytes = new byte[str.len];
            Marshal.Copy(str.content, bytes, 0, (int)str.len);
            return Encoding.UTF8.GetString(bytes);
        }
    }
}
