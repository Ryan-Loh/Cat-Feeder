def sendEmail(mess):
    import smtplib, ssl
    port = 465 # for SSL
    password = "raspiFeeder"
    sender = "pyfeeder@gmail.com"
    receiver = "lydia.nguyen9@gmail.com"
    message = mess

    #Create a secure SSL Context
    context = ssl.create_default_context()

    with smtplib.SMTP_SSL("smtp.gmail.com", port, context = context) as server:
        server.login("pyfeeder@gmail.com", password)
        server.sendmail(sender, receiver, message)
