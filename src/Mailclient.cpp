#include "Mailclient.h"
#include <vmime/vmime.hpp>
#include <iostream>

MailClient::MailClient()
{
    mSession = vmime::make_shared<vmime::net::session>();
}

bool MailClient::sendMail(const std::string& subject, const std::string& message, const std::string& attachment) {
    mBuilder.setSubject(vmime::text(subject));
    mBuilder.setExpeditor(vmime::mailbox("ahmabdabd@hotmail.com"));
    mBuilder.getRecipients().appendAddress(vmime::make_shared<vmime::mailbox>("ahmabdabd@hotmail.com"));
    mBuilder.getTextPart()->setCharset(vmime::charsets::UTF_8);
    mBuilder.getTextPart()->setText(vmime::make_shared<vmime::stringContentHandler>(message));

    vmime::shared_ptr<vmime::message> msg = mBuilder.construct();
    vmime::shared_ptr<vmime::fileAttachment> attach =
            vmime::make_shared<vmime::fileAttachment>(attachment,
                                                      vmime::mediaType("bin"), vmime::text(""));
    vmime::attachmentHelper::addAttachment(msg,attach);

    mTransport->connect();
    mTransport->send(msg);
    mTransport->disconnect();
}

bool MailClient::setConnectionParameters( const std::string& server,const std::string& username,
                              const std::string& pwd="", const std::string& port="")
{
    vmime::utility::url url("smtp://"+username+"@"+server+":"+port);
    mTransport = mSession->getTransport(url);
    mTransport->setProperty("options.need-authentication", true);
    mTransport->setProperty("connection.tls", true);
    mTransport->setProperty("auth.password", pwd);
    vmime::shared_ptr<MailClient::interactiveCertificateVerifier> vrf = vmime::make_shared
            <MailClient::interactiveCertificateVerifier>();
    mTransport->setCertificateVerifier(vrf);
}

std::vector <vmime::shared_ptr <vmime::security::cert::X509Certificate> >
    MailClient::interactiveCertificateVerifier::m_trustedCerts;
