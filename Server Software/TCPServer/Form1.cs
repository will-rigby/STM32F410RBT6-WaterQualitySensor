using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Net;
using System.Net.Sockets;
using System.IO;

namespace waterQualityServer
{
    public partial class Form1 : Form
    {
        bool running = false;
        List<DateTime> times = new List<DateTime>();
        List<String> boardNames = new List<String>();
        List<Int32> sampleNumbers = new List<Int32>();
        List<double> temperatures = new List<double>();
        List<double> conductivitys = new List<double>();
        List<double> pHs = new List<double>();
        List<Int16> depths = new List<Int16>();
        List<Int16> batteryLevels = new List<Int16>();
        List<Int16> signalQualities = new List<Int16>();
        bool workerStarted = false;
        List<String> commandList = new List<String>();
        List<String> boardToSendCommand = new List<String>();
        List<bool> commandSent = new List<bool>();

        List<String> boardList = new List<String>();


        public StreamWriter saveFileWriter;



        public Form1()
        {
            InitializeComponent();

            /* Extract Local IP Address and display in box */
            IPAddress[] localIP = Dns.GetHostAddresses(Dns.GetHostName());
            foreach (IPAddress address in localIP)
            {
                if (address.AddressFamily == AddressFamily.InterNetwork)
                {
                    addressBox.Text = address.ToString();
                }
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void startServerButton_Click(object sender, EventArgs e)
        {
            /* Start Server */
            if (running == false)
            {
                Thread serverThread = new Thread(new ParameterizedThreadStart(serverHandler));
                serverThread.Start();
                running = true;
                runningLabel.Text = "Status: Running";
                startServerButton.Text = "Stop Server";
                dataBox.AppendText("TCP Server Started." + Environment.NewLine);
            }
            else
            {
                running = false;
                startServerButton.Text = "Start Server";
                runningLabel.Text = "Status: Stopped";
                
            }


        }



        private void label2_Click(object sender, EventArgs e)
        {

        }


        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }


        /* Send the set IP command to the board */
        private void setIPButton_Click(object sender, EventArgs e)
        {
            if (setIPBox.Text != "" && boardSelectBox.SelectedItem != null)
            {
                commandList.Add("SETIP=\"" + setIPBox.Text + "\"");
                boardToSendCommand.Add(boardSelectBox.SelectedItem.ToString());
                commandSent.Add(false);
                String messageToPrint = "Stored Message for Sending: SETIP=\"" + setIPBox.Text + "\" to Board :" + boardSelectBox.SelectedItem.ToString() + Environment.NewLine;
                dataBox.AppendText(messageToPrint);

            }
            setIPBox.Text = "";
        }

        /* Send the set name command to the board */
        private void renameButton_Click(object sender, EventArgs e)
        {
            if (setNameBox.Text != "" && boardSelectBox.SelectedItem != null)
            {
                commandList.Add("SETNAME=\"" + setNameBox.Text + "\"");
                boardToSendCommand.Add(boardSelectBox.SelectedItem.ToString());
                commandSent.Add(false);
                String messageToPrint = "Stored Message for Sending: SETNAME=\"" + setNameBox.Text + "\" to Board :" + boardSelectBox.SelectedItem.ToString() + Environment.NewLine;
                dataBox.AppendText(messageToPrint);
            }
            setNameBox.Text = "";
        }

        /* Send the set port command to the board */
        private void setPortButton_Click(object sender, EventArgs e)
        {
            if (setPortBox.Text != "" && boardSelectBox.SelectedItem != null)
            {
                commandList.Add("SETPORT=\"" + setPortBox.Text + "\"");
                boardToSendCommand.Add(boardSelectBox.SelectedItem.ToString());
                commandSent.Add(false);
                String messageToPrint = "Stored Message for Sending: SETPORT=\"" + setPortBox.Text + "\" to Board :" + boardSelectBox.SelectedItem.ToString() + Environment.NewLine;
                dataBox.AppendText(messageToPrint);
            }
            setPortBox.Text = "";
        }

        /* Send the set mobile number command to the board */
        private void setMobileButton_Click(object sender, EventArgs e)
        {
            if (setMobileBox.Text != "" && boardSelectBox.SelectedItem != null)
            {
                commandList.Add("SETMOBILE=\"" + setMobileBox.Text + "\"");
                boardToSendCommand.Add(boardSelectBox.SelectedItem.ToString());
                commandSent.Add(false);
                String messageToPrint = "Stored Message for Sending: SETMOBILE =\"" + setMobileBox.Text + "\" to Board :" + boardSelectBox.SelectedItem.ToString() + Environment.NewLine;
                dataBox.AppendText(messageToPrint);
            }
            setMobileBox.Text = "";
        }

        /* Send the set APN command to the board */
        private void setAPNButton_Click(object sender, EventArgs e)
        {
            if (apnBox.Text != "" && boardSelectBox.SelectedItem != null)
            {
                commandList.Add("SETAPN=\"" + apnBox.Text + "\"");
                boardToSendCommand.Add(boardSelectBox.SelectedItem.ToString());
                commandSent.Add(false);
                String messageToPrint = "Stored Message for Sending: SETAPN =\"" + apnBox.Text + "\" to Board :" + boardSelectBox.SelectedItem.ToString() + Environment.NewLine;
                dataBox.AppendText(messageToPrint);
            }
            apnBox.Text = "";
        }

        /* Send the set interval command to the board */
        private void setIntervalBox_Click(object sender, EventArgs e)
        {
            if (intervalBox.Text != "")
            {
                commandList.Add("SETDELAY=\"" + intervalBox.Text + "\"");
                boardToSendCommand.Add(boardSelectBox.SelectedItem.ToString());
                commandSent.Add(false);
                String messageToPrint = "Stored Message for Sending: SETDELAY=\"" + intervalBox.Text + "\" to Board :" + boardSelectBox.SelectedItem.ToString() + Environment.NewLine;
                dataBox.AppendText(messageToPrint);
            }
            intervalBox.Text = "";
        }

        /* Send the set save location of the csv file */
        private void saveButton_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Filter = "Text Document|*.txt|Comma Separated Values|*.csv";
            if (DialogResult.OK == saveFileDialog1.ShowDialog())
            {
                // If the file name is not an empty string open it for saving.
                if (saveFileDialog1.FileName != "")
                {
                    using (saveFileWriter = new System.IO.StreamWriter(saveFileDialog1.FileName))
                    {
                        saveFileWriter.WriteLine("Time, Board Name, Sample Number, Temperature (C), Conductivity (ppm), pH, Depth, Battery Level (%), SignalQuality");
                        for (int i = 0; i < times.Count; i++)
                        {
                            saveFileWriter.WriteLine(times[i].ToString() + ", " + boardNames[i] + ", " + sampleNumbers[i].ToString() + ", " +
                                temperatures[i].ToString() + ", " + conductivitys[i].ToString() + ", " + pHs[i].ToString()
                                + ", " + depths[i].ToString() + ", " + batteryLevels[i].ToString() + ", " + signalQualities[i].ToString());
                        }

                    }
                }


            }
        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void chart1_Click_1(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        /* Process the received string from the board */
        private void processes_received_message(String receive, StreamWriter toClient)
        {
            if (receive != "")
            {
                Console.WriteLine(receive);

                /* Split received packet by splitting using the commas */
                string[] receivedValues = receive.Split(new[] { ",", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);
                times.Add(DateTime.Now);

                /* If correct number of values add the values to the arrays stored in memory */
                if (receivedValues.Length == 8)
                {
                    boardNames.Add(receivedValues[0]);

                    if (!boardList.Contains(receivedValues[0]))
                    {
                        boardList.Add(receivedValues[0]);
                        this.boardSelectBox.Invoke(new MethodInvoker(delegate () { boardSelectBox.Items.Add(receivedValues[0]); }));
                    }

                    sampleNumbers.Add(Convert.ToInt32(receivedValues[1]));

                    temperatures.Add(Convert.ToDouble(receivedValues[2]));
                    this.chart1.Invoke(new MethodInvoker(delegate () { chart1.Series[0].Points.AddXY(DateTime.Now, Convert.ToDouble(receivedValues[2])); }));

                    conductivitys.Add(Convert.ToDouble(receivedValues[3]));
                    this.chart2.Invoke(new MethodInvoker(delegate () { chart2.Series[0].Points.AddXY(DateTime.Now, Convert.ToDouble(receivedValues[3])); }));

                    pHs.Add(Convert.ToDouble(receivedValues[4]));
                    this.chart3.Invoke(new MethodInvoker(delegate () { chart3.Series[0].Points.AddXY(DateTime.Now, Convert.ToDouble(receivedValues[4])); }));

                    depths.Add(Convert.ToInt16(receivedValues[5]));
                    this.chart4.Invoke(new MethodInvoker(delegate () { chart4.Series[0].Points.AddXY(DateTime.Now, Convert.ToDouble(receivedValues[5])); }));

                    batteryLevels.Add(Convert.ToInt16(receivedValues[7]));
                    this.chart5.Invoke(new MethodInvoker(delegate () { chart5.Series[0].Points.AddXY(DateTime.Now, Convert.ToDouble(receivedValues[7])); }));

                    signalQualities.Add(Convert.ToInt16(receivedValues[6]));

                    String messageToPrint = "Sensor: " + receivedValues[0] + ", " + receivedValues[1] + ", " + receivedValues[2] + ", " + receivedValues[3] + ", " + receivedValues[4] + ", " + receivedValues[5] + ", " + receivedValues[6] + ", " + receivedValues[7] + " at " + DateTime.Now.ToString() + Environment.NewLine;
                    this.dataBox.Invoke(new MethodInvoker(delegate () { dataBox.AppendText(messageToPrint); }));

                    /* Update save file with new data */
                    if (saveFileWriter != null)
                    {
                        using (saveFileWriter = new System.IO.StreamWriter(saveFileDialog1.FileName))
                        {
                            saveFileWriter.WriteLine("Time, Board Name, Sample Number, Temperature (C), Conductivity (ppm), pH, Depth, Battery Level (%), SignalQuality");
                            for (int i = 0; i < times.Count; i++)
                            {
                                saveFileWriter.WriteLine(times[i].ToString() + ", " + boardNames[i] + ", " + sampleNumbers[i].ToString() + ", " +
                                    temperatures[i].ToString() + ", " + conductivitys[i].ToString() + ", " + pHs[i].ToString()
                                    + ", " + depths[i].ToString() + ", " + batteryLevels[i].ToString() + ", " + signalQualities[i].ToString());
                            }

                        }
                    }

                    /* Check if any replies to send to board */
                    for (int i = 0; i < boardToSendCommand.Count(); i++)
                    {
                        Console.WriteLine(i.ToString());
                        if (boardToSendCommand[i].Equals(receivedValues[0])&& commandSent[i]==false)
                        {
                            messageToPrint = "Sent Message To Board: " + commandList[i] + " to Board :" + boardToSendCommand[i] + Environment.NewLine;
                            this.dataBox.Invoke(new MethodInvoker(delegate () { dataBox.AppendText(messageToPrint); }));
                            toClient.Write(commandList[i]);
                            toClient.Flush();
                            commandSent[i] = true;
                        }
                    }


                }
            }
        }


        /* Thread function for handling new TCP client that has connected */
        public void clientHandler(object obj)
        {
            TcpClient client = (TcpClient)obj;
            StreamWriter toClient = new StreamWriter(client.GetStream(), Encoding.ASCII);
            StreamReader fromClient = new StreamReader(client.GetStream(), Encoding.ASCII);
            Console.WriteLine("Client Thread Running");
            bool threadRunning = true;
            while (threadRunning)
            {
                try
                {
                    String receivedData = fromClient.ReadLine();
                    processes_received_message(receivedData, toClient);
                } catch(Exception x)
                {
                    threadRunning = false;
                    Console.WriteLine("Thread Terminated: " + x.ToString());

                }

            }
        }

        private void runningLabel_Click(object sender, EventArgs e)
        {

        }

        /* Thread for listening to the port and accepting new connections */
        public void serverHandler(object obj)
        {
            if (portBox.Text != "")
            {
                TcpListener serverSocket = new TcpListener(IPAddress.Any, int.Parse(portBox.Text));
                serverSocket.Start();
                Console.WriteLine("Server Started");
                while (running)
                {
                    try
                    {
                        /* Wait for TCP Connection */
                        TcpClient newClient = serverSocket.AcceptTcpClient();
                        Thread clientThread = new Thread(new ParameterizedThreadStart(clientHandler));
                        clientThread.Start(newClient);
                        Console.WriteLine("Client Accepted");
                    }
                    catch (Exception x)
                    {
                        Console.WriteLine("Accepting Client Failed: " + x.ToString());
                    }

                }

            }
        }
    }
}

