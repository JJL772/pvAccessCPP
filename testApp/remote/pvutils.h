#include <pv/event.h>
#include <pv/pvData.h>
#include <pv/pvAccess.h>

/// terse mode functions
void convertStructure(epics::pvData::StringBuilder buffer, epics::pvData::PVStructure *data, int notFirst);
void convertArray(epics::pvData::StringBuilder buffer, epics::pvData::PVScalarArray * pv, int notFirst);
void convertStructureArray(epics::pvData::StringBuilder buffer, epics::pvData::PVStructureArray * pvdata, int notFirst);

void terseSeparator(char c);
std::ostream& terse(std::ostream& o, epics::pvData::PVField::shared_pointer const & pv);
std::ostream& terseStructure(std::ostream& o, epics::pvData::PVStructure::shared_pointer const & pvStructure);
std::ostream& terseScalarArray(std::ostream& o, epics::pvData::PVScalarArray::shared_pointer const & pvArray);
std::ostream& terseStructureArray(std::ostream& o, epics::pvData::PVStructureArray::shared_pointer const & pvArray);


/* Converts a hex character to its integer value */
char from_hex(char ch);

/* Converts an integer value to its hex character*/
char to_hex(char code);

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_encode(const char *str);


class RequesterImpl :
	public epics::pvData::Requester
{
    public:
	    RequesterImpl(epics::pvData::String const & requesterName);
        virtual epics::pvData::String getRequesterName();
        virtual void message(epics::pvData::String const & message, epics::pvData::MessageType messageType);

    private:
        epics::pvData::String m_requesterName;
};

class ChannelRequesterImpl :
    public epics::pvAccess::ChannelRequester
{
    private:
        epics::pvData::Event m_event;
    
    public:
        virtual epics::pvData::String getRequesterName();
        virtual void message(epics::pvData::String const & message, epics::pvData::MessageType messageType);
    
        virtual void channelCreated(const epics::pvData::Status& status, epics::pvAccess::Channel::shared_pointer const & channel);
        virtual void channelStateChange(epics::pvAccess::Channel::shared_pointer const & channel, epics::pvAccess::Channel::ConnectionState connectionState);
    
        bool waitUntilConnected(double timeOut);
};
