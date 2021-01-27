using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GenerationLib
{
    public class GenText
    {

        const int amWords = 5;

        public void CreateText(string path, string str)
        {
            char[] simb1 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
            ulong sz;
            FileStream file;
            StreamWriter FW;
            try
            {
                sz = (ulong)Convert.ToInt64(str);
                sz = sz / 2;
                file = new FileStream(path, FileMode.Create);
                FW = new StreamWriter(file, System.Text.Encoding.Unicode);
            }
            catch
            {
                return;
            }
            if (sz == 0)
                sz = (1024 * 1024 * 1024) / 2;
            ulong f = 0;
            Random rnd = new Random();
            Random smb = new Random();
            for (ulong j = 0; j < sz; j++)
            {
                for (int i = 0; i < amWords; i++)
                {
                    uint sh = (uint)rnd.Next(7, 30);
                    for (int s = 0; s < sh; s++)
                    {
                        int b = smb.Next(0, simb1.Length - 1);
                        FW.Write(simb1[b]);
                        f++;
                        if (f == sz)
                            goto M;
                    }
                    FW.Write(" ");
                    f++;
                    if (f == sz)
                        goto M;
                }
                FW.WriteLine();
                f++;
                if (f == sz)
                    goto M;
                f++;
                if (f == sz)
                    goto M;
            }
        M:
            FW.Close();
        }
    }
}
