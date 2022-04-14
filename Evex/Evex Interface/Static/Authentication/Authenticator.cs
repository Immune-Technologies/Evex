using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Management;
using System.Net;

namespace Evex.Authentication
{
    public class HardwareInfo
    {
        public static string ProcesserId()
        {
            string PartName = string.Empty;
            ManagementObjectCollection ManagementBaseObjects = new ManagementClass("win32_processor").GetInstances();

            foreach (var Object in ManagementBaseObjects)
                PartName = Object.Properties["processorID"].Value.ToString();

            return PartName;
        }

        public static string DeviceId()
        {
            string PartName = string.Empty;
            ManagementObjectCollection ManagementBaseObjects = new ManagementClass("win32_processor").GetInstances();

            foreach (var Object in ManagementBaseObjects)
                PartName = Object.Properties["DeviceID"].Value.ToString();

            return PartName;
        }

        public static string GetUniqueId() => Convert.ToBase64String(Encoding.UTF8.GetBytes(ProcesserId() + DeviceId()));
    }

    internal class Authenticator
    {
        /* 
         * Use Pastebin Or Github And Format It With Each Hardware ID On Each New Line
         * To Grab Hardware Id Send Call GenerateId Anywhere And Set It To Clipboard Or Something 
         */

        public static bool IsBanned(string Url)
        {
            var UserId = Encoding.UTF8.GetString(Convert.FromBase64String(HardwareInfo.GetUniqueId()));
            string[] List = null;

            using (var Http = new WebClient { Proxy = null })
                List = Http.DownloadString(Url).Split("\r\n".ToCharArray());

            foreach (var HardwareId in List)
                if (UserId == HardwareId || List.Contains(UserId))
                    return true;

            return false;
        }
    }
}
