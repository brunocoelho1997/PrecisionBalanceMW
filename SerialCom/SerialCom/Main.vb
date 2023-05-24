Imports System
Imports System.Threading
Imports System.IO.Ports
Imports System.ComponentModel
Imports System.Drawing.Printing
Imports System.Drawing.Graphics
Imports System.Drawing.Imaging
Imports System.Runtime.InteropServices
Public Class Main
    Dim comOpen As Boolean      'Keeps track of the port status. True = Open; False = Closed
    Dim readbuffer As String    'Buffer of whats read from the serial port
    Private _left As String
    '------------------------------------------------
    Dim myPort As Array
    Delegate Sub SetTextCallback(ByVal [text] As String) 'Added to prevent threading errors during receiveing of data
    '------------------------------------------------
    Dim ToolTipProvider As New ToolTip
    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        With SerialPort1
            .PortName = My.Settings.Porta '"Com3"               'Selected Port
            .BaudRate = CInt(9600)      'Baud Rate. 9600 is default.
            .Parity = IO.Ports.Parity.None
            .DataBits = 8
            .StopBits = IO.Ports.StopBits.One
            .Handshake = IO.Ports.Handshake.None
            .RtsEnable = False
            .ReceivedBytesThreshold = 1
            .NewLine = vbCr
            .ReadTimeout = 10000
        End With
        'Try to open the selected port...
        Try
            SerialPort1.Open()
            comOpen = SerialPort1.IsOpen
        Catch ex As Exception
            comOpen = False
            MsgBox("Error Open: " & ex.Message)
        End Try

        ' Panel1.Location = New Point(30, 90)
        Panel1.Size = New Size(350, 150)

    End Sub
    Private Sub Button4_Click(sender As System.Object, e As System.EventArgs) Handles Button4.Click
        SerialPort1.Close()
        Close()
        Button4.Enabled = False
    End Sub
    Private Sub SerialPort1_DataReceived(sender As System.Object, e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        ReceivedText(SerialPort1.ReadExisting())
        If comOpen Then
            Try
                readbuffer = SerialPort1.ReadLine()
                Me.Invoke(New EventHandler(AddressOf updateValue))
            Catch ex As Exception
            End Try
        End If
    End Sub
    Private Sub ReceivedText(ByVal [text] As String) 'input from ReadExisting
        If Me.TextBox10.InvokeRequired Then
            Dim x As New SetTextCallback(AddressOf ReceivedText)
            Me.Invoke(x, New Object() {(text)})
        Else
            Me.TextBox10.Text &= [text] 'append text
        End If
    End Sub
    Public Sub updateValue(ByVal sender As Object, ByVal e As System.EventArgs)

        'Declaração de variáveis
        Dim read As String
        Dim x As Double
        Dim x1 As Double
        Dim x2 As Double
        Dim x3 As Double
        Dim xx1 As Double
        Dim xx2 As Double
        Dim xx3 As Double
        Dim xx4 As Double
        Dim yy1 As Double
        Dim yy2 As Double
        Dim yy3 As Double
        Dim yy4 As Double
        Dim Xcg As Double
        Dim Ycg As Double
        Dim Xcgt As Double
        Dim Ycgt As Double
        Dim tb1 As Double
        Dim tb2 As Double
        Dim tb3 As Double
        Dim tb4 As Double
        Dim tb5 As Double
        Dim const1 As Double
        Dim const2 As Double

        read = readbuffer '.Replace(vbCr, "").Replace(vbLf, "")
        TextBox10.Text = read
        Dim Dimensão As Integer = Len(read)
        Configurations.TextBox2.Text = Dimensão

        const1 = Panel1.Size.Width
        const2 = Panel1.Size.Height
        If Dimensão > 30 Then
            Dim arreyvaue As String() = Split(read, " ")
            TextBox1.Text = arreyvaue(1)
            TextBox2.Text = arreyvaue(2)
            TextBox3.Text = arreyvaue(3)
            TextBox4.Text = arreyvaue(4)
            TextBox5.Text = arreyvaue(5)
            TextBox9.Text = arreyvaue(6)


            Plataforma.TextBox1.Text = arreyvaue(0)
            Plataforma.TextBox1.Text = arreyvaue(1)
            Plataforma.TextBox2.Text = arreyvaue(2)
            Plataforma.TextBox3.Text = arreyvaue(3)
            Plataforma.TextBox4.Text = arreyvaue(4)
            Plataforma.TextBox5.Text = arreyvaue(5)
            Plataforma.TextBox6.Text = arreyvaue(6)
            Plataforma.TextBox7.Text = arreyvaue(7)
            Plataforma.TextBox8.Text = arreyvaue(8)
            Plataforma.TextBox9.Text = arreyvaue(9)
            Plataforma.TextBox10.Text = arreyvaue(10)
            Plataforma.TextBox11.Text = arreyvaue(11)
            Plataforma.TextBox12.Text = arreyvaue(12)
            Plataforma.TextBox13.Text = arreyvaue(13)
            Plataforma.TextBox14.Text = arreyvaue(14)
            Plataforma.TextBox15.Text = arreyvaue(15)
            'Plataforma.TextBox16.Text = arreyvaue(16)

            tb1 = CDbl(TextBox1.Text) / 100
            tb2 = CDbl(TextBox2.Text) / 100
            tb3 = CDbl(TextBox3.Text) / 100
            tb4 = CDbl(TextBox4.Text) / 100
            tb5 = CDbl(TextBox9.Text) / 100

            x = (tb2 + tb4) * 130

            If x = 0 Then
                x = 165
            Else
                If ((tb1 + tb3) + (tb2 + tb4)) > 0 Then
                    x1 = x / ((tb1 + tb3) + (tb2 + tb4))
                Else
                    x1 = 65
                End If
            End If

            x2 = (tb3 + tb4) * 330
            If x2 = 0 Then
                x2 = 165
            Else
                If ((tb1 + tb2) + (tb3 + tb4)) > 0 Then
                    x3 = x2 / ((tb1 + tb2) + (tb3 + tb4))
                Else
                    x3 = 165
                End If
            End If
        End If

        PictureBox1.Location = New Point(x3, x1)

        xx1 = 9.5
        xx2 = 9.5
        xx3 = 70
        xx4 = 70

        yy1 = 4.5
        yy2 = 39
        yy3 = 39
        yy4 = 4.5

        Xcg = ((xx1 * tb2) + (xx2 * tb1) + (xx3 * tb3) + (xx4 * tb4)) / (tb1 + tb2 + tb3 + tb4)
        Ycg = ((yy1 * tb2) + (yy2 * tb1) + (yy3 * tb3) + (yy4 * tb4)) / (tb1 + tb2 + tb3 + tb4)

        If (tb1 + tb2 + tb3 + tb4) < 0 Or ((xx1 * tb2) + (xx2 * tb1) + (xx3 * tb3) + (xx4 * tb4)) < 0 Or ((yy1 * tb2) + (yy2 * tb1) + (yy3 * tb3) + (yy4 * tb4)) < 0 Then
            Xcg = 0
            Ycg = 0
        Else

            Xcgt = ((xx1 * tb2) + (xx2 * tb1) + (xx3 * tb3) + (xx4 * tb4)) / (tb1 + tb2 + tb3 + tb4)
            Ycgt = ((yy1 * tb2) + (yy2 * tb1) + (yy3 * tb3) + (yy4 * tb4)) / (tb1 + tb2 + tb3 + tb4)

            If Xcgt < 0 Or Xcgt > 90 Or Xcgt < 0 Or Xcgt > 55 Then
                Xcg = 0
                Ycg = 0
            Else
                Xcg = Xcgt
                Ycg = Ycgt
            End If

        End If

        TextBox6.Text = Xcg
        TextBox7.Text = Ycg


        With Chart1.ChartAreas(0)
            .AxisX.MajorGrid.Enabled = False
            .AxisY.MajorGrid.Enabled = False
            Chart1.Series(0).Points.Clear()
            Chart1.Series(1).Points.Clear()
        End With

        Chart1.Series(0).Points.AddXY(Xcg, Ycg)

        'Bounding box

        Chart1.Series(1).Points.AddXY(tb5, Ycg + (TextBox12.Text / 2))
        Chart1.Series(1).Points.AddXY(tb5, Ycg - (TextBox12.Text / 2))

        Chart1.Series(1).Points.AddXY(tb5 + TextBox11.Text, Ycg + (TextBox12.Text / 2))
        Chart1.Series(1).Points.AddXY(tb5 + TextBox11.Text, Ycg - (TextBox12.Text / 2))

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Configurations.Show()
        SerialPort1.Close()
    End Sub
    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        SerialPort1.Write("T" & vbCr)
    End Sub
    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Try
            SerialPort1.Open()
            comOpen = SerialPort1.IsOpen
        Catch ex As Exception
            comOpen = False
            MsgBox("Error Open: " & ex.Message)
        End Try
    End Sub
    Private Sub Chart1_MouseMove(sender As Object, e As MouseEventArgs) Handles Chart1.MouseMove
        Dim h As Windows.Forms.DataVisualization.Charting.HitTestResult = Chart1.HitTest(e.X, e.Y)
        If h.ChartElementType = DataVisualization.Charting.ChartElementType.DataPoint Then
            ToolTipProvider.SetToolTip(Chart1, h.Series.Points(h.PointIndex).XValue & " x " & h.Series.Points(h.PointIndex).YValues(0))
        End If
    End Sub


    Private Sub Acquire_Click(sender As Object, e As EventArgs) Handles Acquire.Click
        TextBox13.Text = TextBox5.Text

    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        TextBox14.Text = TextBox5.Text
        If TextBox14.Text = "0.00" Then
            MsgBox("Conversão impossivel", 0, "ERRO")
        Else
            TextBox15.Text = (CDbl(TextBox14.Text) * 100) / CDbl(TextBox13.Text)
        End If

    End Sub


    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        Plataforma.Show()
    End Sub
End Class

