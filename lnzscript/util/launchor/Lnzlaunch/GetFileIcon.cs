using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Runtime.InteropServices;

namespace Lnzlaunch
{

    //http://www.codeguru.com/csharp/csharp/cs_misc/icons/article.php/c4261/

    public class GetFileIcon
    {
        public const uint SHGFI_ICON = 0x100;
        public const uint SHGFI_LARGEICON = 0x0;    // 'Large icon
        public const uint SHGFI_SMALLICON = 0x1;    // 'Small icon

        [DllImport("shell32.dll")]
        public static extern IntPtr SHGetFileInfo(string pszPath,
                                    uint dwFileAttributes,
                                    ref SHFILEINFO psfi,
                                    uint cbSizeFileInfo,
                                    uint uFlags);
        [DllImport("user32")]
        public static extern int DestroyIcon(IntPtr hIcon);


        [StructLayout(LayoutKind.Sequential)]
        public struct SHFILEINFO
        {
            public IntPtr hIcon;
            public IntPtr iIcon;
            public uint dwAttributes;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
            public string szDisplayName;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 80)]
            public string szTypeName;
        };

        public static Icon Getfileicon(string sFilename)
        {
            IntPtr hImgLarge;
            //Use this to get the small Icon
            /*hImgSmall = Win32.SHGetFileInfo(fName, 0, ref shinfo,
                                           (uint)Marshal.SizeOf(shinfo),
                                            Win32.SHGFI_ICON |
                                            Win32.SHGFI_SMALLICON);*/
            SHFILEINFO shinfo = new SHFILEINFO();


            //Use this to get the large Icon
            hImgLarge = SHGetFileInfo(sFilename, 0,
                ref shinfo, (uint)Marshal.SizeOf(shinfo), SHGFI_ICON | SHGFI_LARGEICON);

            if (hImgLarge == IntPtr.Zero)
                return null; //couldn't find an icon
            //The icon is returned in the hIcon member of the shinfo
            
            System.Drawing.Icon myIcon = (Icon) System.Drawing.Icon.FromHandle(shinfo.hIcon).Clone();
            DestroyIcon(shinfo.hIcon);
            return myIcon;
        }

    }
}
