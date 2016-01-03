using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
using System.Management;
using System.Net;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using System.Text;

namespace SignIn
{
	static class UserFunction
	{
		static public string GetSemester()
		{
			string Semester = string.Empty;
			string str = "select 学期 from [开学日期]";
			DatabaseCmd databasecmd = new DatabaseCmd();
			SqlDataReader myreader;
			databasecmd.SqlExecuteReader(str, out myreader);
			if(myreader.Read())
			{
				Semester = myreader.GetString(0);
			}
			databasecmd.SqlReaderClose();
			return Semester;
		}

		static public DateTime GetServerTime()
		{
			string str = "select getdate() as serverDate";
			DatabaseCmd datacmd = new DatabaseCmd();
			SqlDataReader myreader;
			try
			{
				datacmd.SqlExecuteReader(str, out myreader);
				if (myreader.Read())
				{
					return myreader.GetDateTime(0);
				}
				else
				{
					return DateTime.Now;
				}
			}
			catch (Exception ex)
			{
				System.Windows.Forms.MessageBox.Show(ex.Message);
				return DateTime.Now;
			}
			finally
			{
				datacmd.SqlReaderClose();
			}
		}

		static public void RegistryCmd()
		{
			RegistryKey reg = null;
			if (Registry.CurrentUser.OpenSubKey(@"Software\ELAB\科中管理系统_签到").SubKeyCount <= 0)
			{
				Registry.CurrentUser.CreateSubKey(@"Software\ELAB\科中管理系统_签到");
			}
		}

		static public int GetWeek()
		{
			int week = 0;
			string str = @"select top 1 datediff(day,[开学日期],getdate())/7+1 from [开学日期]";
			DatabaseCmd databasecmd = new DatabaseCmd();
			SqlDataReader myreader = null;
			databasecmd.SqlExecuteReader(str, out myreader);
			week = (myreader.Read()) ? (myreader.GetInt32(0)) : (-1);
			databasecmd.SqlReaderClose();
			return week;
		}

		static public string GetIP()
		{
			string tempip = "";
			try
			{
				WebRequest wr = WebRequest.Create("http://www.ip138.com/ips138.asp");
				Stream s = wr.GetResponse().GetResponseStream();
				StreamReader sr = new StreamReader(s, Encoding.Default);
				string all = sr.ReadToEnd(); //读取网站的数据

				int start = all.IndexOf("您的IP地址是：[") + 9;
				int end = all.IndexOf("]", start);
				tempip = all.Substring(start, end - start);
				sr.Close();
				s.Close();
			}
			catch
			{
			}
			return tempip;
		}

		///<summary>
		/// 通过NetworkInterface读取网卡Mac
		///</summary>
		///<returns></returns>
		public static string GetMacByNetworkInterface()
		{
			string mac = "";
			ManagementClass mc = new ManagementClass("Win32_NetworkAdapterConfiguration");
			ManagementObjectCollection moc = mc.GetInstances();
			foreach (ManagementObject mo in moc)
			{
				if (mo["IPEnabled"].ToString() == "True")
				{
					mac = mo["MacAddress"].ToString();
				}
			}
			return mac;
		}
	}
}
