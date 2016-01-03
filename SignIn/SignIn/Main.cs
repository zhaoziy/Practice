using System;
using System.Data.SqlClient;
using System.Diagnostics;
using System.Windows.Forms;

namespace SignIn
{
	public partial class Main : Form
	{
		static private int Version = 1;
		static public string SoftName = "科中管理系统_签到";
		static private string Semester = string.Empty;
		static private DateTime SignInTime = DateTime.Now;
		static private int NowWeek = 0;
		static private bool IsFirstRun = true;
		static private bool IsBackTip = true;
		static private string PublicIP = string.Empty;
		static private int UserType = 0;      //1代表内网用户，2代表Dlut用户，0代表非法用户
		static private bool IsSignIn = false;            //是否已签到
		static UserInfo userinfo;
		static private string Sign_Identity = string.Empty;
		static private float OnlineTime = 0.0f;
		static private DateTime NowTime;
		
		public Main()
		{
			InitializeComponent();

			Semester = UserFunction.GetSemester();
			SignInTime = UserFunction.GetServerTime();
			NowWeek = UserFunction.GetWeek();                   //获取周次
			PublicIP = UserFunction.GetIP();
			UserType = GetUserType();
			if (UserType == 0)
			{
				MessageBox.Show("请进入科中范围使用");
				Application.Exit();
			}
			Initialization();
			Sign();
			UpdateInfo();
			OnlineTime = SumOnlineTime();
		}

		private void UpdateInfo()
		{
			this.TextBName.Text = userinfo.UserName;
			this.TextBNum.Text = userinfo.StuNum;
			this.TextBTeam.Text = userinfo.Team;
			this.TextBGrade.Text = userinfo.Grade;
			this.TextBSign.Text = SignInTime.ToString("T");
			this.TextBPhone.Text = userinfo.Phone;
			this.TextBMotto.Text = userinfo.HappyMotto;
			this.ButChange.Enabled = false;
		}

		private float SumOnlineTime()
		{
			float OnlineTime = -1;
			string str_time = "select SUM(合计时间) from 时间统计 where 学号 = '" +
				userinfo.StuNum + "' and 周次 = " + NowWeek + " and 学期 ='" + Semester + "'";
			DatabaseCmd databasecmd = new DatabaseCmd();
			SqlDataReader myreader;
			databasecmd.SqlExecuteReader(str_time, out myreader);
			if(myreader.Read())
			{
				OnlineTime = (float)myreader.GetDouble(0);
			}
			databasecmd.SqlReaderClose();
			return OnlineTime;
		}

		private void Sign()
		{
			//检测上次是否正常退出(今天范围内)，如果不是，将上次未签退的记录以0小时退掉，并将离开字段=登入字段(因为智能考核系统是以离开字段=0获取在线用户的)
			DatabaseCmd databasecmd = new DatabaseCmd();
			string str = "update 时间统计 set 离开=登入 where 离开='0' and 日期='" + 
				SignInTime.Year + "-" + SignInTime.Month + "-" + SignInTime.Day +
				"' and 学号='" + userinfo.StuNum + "'";
			if (!databasecmd.SqlExecuteNonQuery(str))
			{
				MessageBox.Show("出现致命错误！程序将强制退出！");
				IsSignIn = false;
				Application.Exit();
			}

			if (SignInTime.Year != 1991)
			{
				string str1 = string.Empty;

				str1 = "insert into 时间统计(学号,姓名,组别,日期,周次,登入,离开,合计时间,学期) values ('" +
				 userinfo.StuNum + "','" + userinfo.user + "','" + userinfo.Team + "','" +
				 SignInTime.Year + "-" + SignInTime.Month + "-" + SignInTime.Day + "','" +
				 NowWeek + "','" + SignInTime.ToString("T") + "','" + "0" + "','" + "0" + "','" +
				 Semester + "')" + " select scope_identity() as id";

				try
				{
					object index;
					databasecmd.SqlExecuteScalar(str1, out index);
					Sign_Identity = index.ToString();
					IsSignIn = true;
				}
				catch (Exception ex)
				{
					MessageBox.Show(ex.ToString());
					Application.Exit();
				}
			}
		}

		private void Initialization()
		{
			this.Opacity = 0;
			this.TextBMotto.Focus();
			this.Label1.Text = "版本号：" + Version;
			string startupPath = Application.StartupPath;

			if (startupPath.Substring(0, 2) == @"\\")
			{
				MessageBox.Show("请不要在服务器上运行，请安装到本地后再运行。");
				Application.Exit();
			}

			//检测程序是否已经在运行
			if (Process.GetProcessesByName(Process.GetCurrentProcess().ProcessName).Length > 1)
			{
				MessageBox.Show("检测到程序正在运行！");
				Application.Exit();
			}

			if (!GetInfo(out userinfo))
			{
				MessageBox.Show("出现未知错误，程序将退出！");
				Application.Exit();
			}
		}

		private int GetUserType()
		{
			string[] IPArrray = new string[4];
			IPArrray = PublicIP.Split('.');
			if (IPArrray[0] == "202" && IPArrray[1] == "118" && IPArrray[2] == "74")
			{
				return 1;
			}
			else if (IPArrray[0] == "202" && IPArrray[1] == "118" && IPArrray[2] == "111")
			{
				return 2;
			}
			else
			{
				return 0;
			}
		}

		private bool GetInfo(out UserInfo userinfo)
		{
			string str = string.Empty;
			if (UserType == 1)
			{
				str = @"select UserName,学号,姓名,组别,电话,座右铭,年级 from [member] where USERNAME='" +
					Environment.GetEnvironmentVariable("username") + "'";
			}
			else if (UserType == 2)
			{
				str = @"select UserName,学号,姓名,组别,电话,座右铭,年级 from [member] where MAC='" +
					UserFunction.GetMacByNetworkInterface() + "'";
			}

			DatabaseCmd databasecmd = new DatabaseCmd();
			SqlDataReader myreader;
			databasecmd.SqlExecuteReader(str, out myreader);
			if (myreader.Read())
			{
				userinfo.UserName = myreader.GetString(0).ToString();
				userinfo.StuNum = myreader.GetString(1).ToString();
				userinfo.user = myreader.GetString(2).ToString();
				userinfo.Team = myreader.GetString(3).ToString();
				userinfo.Phone = myreader.GetString(4).ToString();
				userinfo.HappyMotto = myreader.GetString(5).ToString();
				userinfo.Grade = myreader.GetString(6).ToString();
				return true;
			}
			else
			{
				userinfo.UserName = "";
				userinfo.StuNum = "";
				userinfo.user = "";
				userinfo.Team = "";
				userinfo.Phone = "";
				userinfo.HappyMotto = "";
				userinfo.Grade = "";
				return false;
			}
		}

		struct UserInfo
		{
			public string UserName;
			public string StuNum;
			public string user;
			public string Team;
			public string Phone;
			public string HappyMotto;
			public string Grade;
		}

		private void Main_KeyDown(object sender, KeyEventArgs e)
		{
			if(e.KeyCode == Keys.Escape)
			{
				ShowOrHide(false);
			}
		}

		private void ShowOrHide(bool IsShow)
		{
			详细信息ToolStripMenuItem.Checked = IsShow;
			if(IsShow)
			{
				NowTime = UserFunction.GetServerTime();
				if(NowTime.Year == 1991)
				{
					toolStripStatusLabel2.Text = "获取失败";
				}
				else
				{
					toolStripStatusLabel2.Text = NowTime.ToShortDateString() + " " +
						NowTime.ToLongTimeString();
					NowTime = NowTime.AddSeconds(1);
				}
			}
			this.Visible = IsShow;
		}

		private void Main_Shown(object sender, EventArgs e)
		{
			this.Hide();
			this.Opacity = 1;
			详细信息ToolStripMenuItem.Checked = false;
		}

		private void notifyIcon1_DoubleClick(object sender, EventArgs e)
		{
			this.ShowOrHide(!this.Visible);
		}

		private void 详细信息ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.ShowOrHide(!this.Visible);
		}

		private void 开机启动ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.开机启动ToolStripMenuItem.Checked = !this.开机启动ToolStripMenuItem.Checked;
			if(开机启动ToolStripMenuItem.Checked)
			{
			}
			else
			{
			}
		}

		private void 退出程序ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}

		private void notifyIcon1_MouseMove(object sender, MouseEventArgs e)
		{
			notifyIcon1.Text = "当前在线时间为：" + OnlineTime + "小时";
		}

		private void TextBPhone_TextChanged(object sender, EventArgs e)
		{
			this.ButChange.Enabled = true;
			this.ButChange.Text = "应用设置";
		}

		private void ButChange_Click(object sender, EventArgs e)
		{
			bool islegal = true;
			for(int i = 0; i<TextBPhone.Text.Length; ++i )
			{
				if(!Char.IsNumber(TextBPhone.Text, i))
				{
					islegal = false;
				}
			}
			if(islegal)
			{
				ButChange.Enabled = false;
				ButChange.Text = "稍后....";
				string str = @"update [member] set [电话]='" + TextBPhone.Text.Trim() + 
					"',[座右铭]='" + TextBMotto.Text.Trim() + "' where [学号]='" +
					userinfo.StuNum + "'";
				DatabaseCmd database = new DatabaseCmd();
				if(!database.SqlExecuteNonQuery(str))
				{
					MessageBox.Show("更新失败！请检查网络连接");
					ButChange.Enabled = true;
					ButChange.Text = "应用设置";
					ButChange.Focus();
				}
				else
				{
					userinfo.Phone = TextBPhone.Text.Trim();
					userinfo.HappyMotto = TextBMotto.Text.Trim();
					ButChange.Text = "设置成功";
					TextBMotto.Focus();
				}
			}
			else
			{
				errorProvider1.SetError(TextBPhone, "只允许使用数字！");
				TextBPhone.Focus();
			}
		}

		private void Main_FormClosing(object sender, FormClosingEventArgs e)
		{

		}
	}
}