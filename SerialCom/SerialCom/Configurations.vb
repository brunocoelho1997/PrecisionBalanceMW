

Public Class Configurations
    Dim myPort As Array

    Private Property SerialPort1 As Object

    Delegate Sub SetTextCallback(ByVal [text] As String) 'Added to prevent threading errors during receiveing of data
    '------------------------------------------------
    Private Sub Configurações_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        TextBox3.Text = My.Settings.Porta
        myPort = IO.Ports.SerialPort.GetPortNames()
        ComboBox1.Items.AddRange(myPort)
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        ' Open the Serial Port
        SerialPort1.Open()

        'Writes data to the Serial Port output buffer 
        If SerialPort1.IsOpen = True Then
            SerialPort1.Write("T")
        End If

        'SerialPort1.Form1.Write(TextBox1.Text & vbCr) 'concatenate with \n
    End Sub


    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        My.Settings.Porta = ComboBox1.Text
        My.Settings.Save()
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Hide()
    End Sub

End Class