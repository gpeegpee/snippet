//http://www.codeproject.com/Articles/6614/Generic-Observer-Pattern-and-Events-in-C

// Event handler base for delegate with 1 parameter
template <typename ReturnT,typename ParamT>
class EventHandlerBase1
{
public:
    virtual ReturnT notify(ParamT param) = 0;
};

template <typename ListenerT,typename ReturnT,typename ParamT>
class EventHandler1 : public EventHandlerBase1<ReturnT,ParamT>
{
    typedef ReturnT (ListenerT::*PtrMember)(ParamT);
    ListenerT* m_object;
    PtrMember m_member;

public:

    EventHandler1(ListenerT* object, PtrMember member)
        : m_object(object), m_member(member)
    {}

    ReturnT notify(ParamT param)
    {
        return (m_object->*m_member)(param);
    }
};

template <typename ReturnT,typename ParamT>
class CppEvent1
{
    typedef std::map<int,EventHandlerBase1<ReturnT,ParamT> *> HandlersMap;
    HandlersMap m_handlers;
    int m_count;

public:


    CppEvent1()
        : m_count(0) {}

    template <typename ListenerT>
    CppEventHandler attach(ListenerT* object,ReturnT (ListenerT::*member)(ParamT))
    {
        typedef ReturnT (ListenerT::*PtrMember)(ParamT);
        m_handlers[m_count] = (new EventHandler1<ListenerT,
                                ReturnT,ParamT>(object,member));
        m_count++;
        return m_count-1;
    }

    bool detach(CppEventHandler id)
    {
        HandlersMap::iterator it = m_handlers.find(id);

        if(it == m_handlers.end())
            return false;

        delete it->second;
        m_handlers.erase(it);
        return true;
    }

    ReturnT notify(ParamT param)
    {
        HandlersMap::iterator it = m_handlers.begin();
        for(; it != m_handlers.end(); it++)
        {
            it->second->notify(param);
        }

        return true;
    }
};
