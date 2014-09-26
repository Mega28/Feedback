#ifndef MAILCLIENT_H
#define MAILCLIENT_H
#include <vmime/vmime.hpp>

class MailClient
{
public:
    MailClient();
    bool setConnectionParameters( const std::string& server,const std::string& username,
                                  const std::string& pwd, const std::string& port);
    bool sendMail(const std::string& subject, const std::string& message,
                  const std::string& attachment);
private:
    vmime::messageBuilder mBuilder;
    vmime::shared_ptr<vmime::net::session> mSession;
    vmime::shared_ptr<vmime::net::transport> mTransport;


    // Certificate verifier (TLS/SSL)
    class interactiveCertificateVerifier : public vmime::security::cert::defaultCertificateVerifier
    {
    public:

        void verify(vmime::shared_ptr <vmime::security::cert::certificateChain> chain, const vmime::string& hostname)
        {
            try
            {
                setX509TrustedCerts(m_trustedCerts);

                defaultCertificateVerifier::verify(chain, hostname);
            }
            catch (vmime::exceptions::certificate_verification_exception&)
            {
                // Obtain subject's certificate
                vmime::shared_ptr <vmime::security::cert::certificate> cert = chain->getAt(0);

    //            std::cout << std::endl;
    //            std::cout << "Server sent a '" << cert->getType() << "'" << " certificate." << std::endl;
    //            std::cout << "Do you want to accept this certificate? (Y/n) ";
    //            std::cout.flush();

    //            std::string answer;
    //            std::getline(std::cin, answer);

    //            if (answer.length() != 0 &&
    //                (answer[0] == 'Y' || answer[0] == 'y'))
    //            {
                    // Accept it, and remember user's choice for later
                    if (cert->getType() == "X.509")
                    {
                        m_trustedCerts.push_back(vmime::dynamicCast
                            <vmime::security::cert::X509Certificate>(cert));

                        setX509TrustedCerts(m_trustedCerts);
                        defaultCertificateVerifier::verify(chain, hostname);
                    }

                    return;
    //            }

    //            throw vmime::exceptions::certificate_verification_exception
    //                ("User did not accept the certificate.");
            }
        }

    private:

        static std::vector <vmime::shared_ptr <vmime::security::cert::X509Certificate> > m_trustedCerts;
    };

};



#endif // MAILCLIENT_H
