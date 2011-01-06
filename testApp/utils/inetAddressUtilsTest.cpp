/*
 * inetAddressUtilsTest.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: user
 */

#include "inetAddressUtil.h"

#include <byteBuffer.h>
#include <pvType.h>
#include <epicsAssert.h>
#include <iostream>
#include <cstring>

using namespace epics::pvAccess;
using std::cout;
using std::endl;
using std::stringstream;
using std::hex;

int main(int argc, char *argv[]) {

    InetAddrVector *vec;
    InetAddrVector *vec1;

    cout<<"Testing \"getSocketAddressList\""<<endl;
    vec = getSocketAddressList("127.0.0.1   10.10.12.11:1234 192.168.3.4", 555);

    assert(vec->size()==3);

    osiSockAddr* addr;
    addr = vec->at(0);
    assert(addr->ia.sin_family==AF_INET);
    assert(addr->ia.sin_port==htons(555));
    assert(addr->ia.sin_addr.s_addr==htonl(0x7F000001));
    assert(inetAddressToString(addr)=="127.0.0.1:555");
    cout<<'\t'<<inetAddressToString(addr, true)<<endl;

    addr = vec->at(1);
    assert(addr->ia.sin_family==AF_INET);
    assert(addr->ia.sin_port==htons(1234));
    assert(addr->ia.sin_addr.s_addr==htonl(0x0A0A0C0B));
    assert(inetAddressToString(addr)=="10.10.12.11:1234");
    cout<<'\t'<<inetAddressToString(addr, true)<<endl;

    addr = vec->at(2);
    assert(addr->ia.sin_family==AF_INET);
    assert(addr->ia.sin_port==htons(555));
    assert(addr->ia.sin_addr.s_addr==htonl(0xC0A80304));
    assert(inetAddressToString(addr)=="192.168.3.4:555");
    cout<<'\t'<<inetAddressToString(addr, true)<<endl;

    cout<<"\nPASSED!\n";

    cout<<"Testing \"getSocketAddressList\" with append"<<endl;

    vec1 = getSocketAddressList("172.16.55.160", 6789, vec);
    assert(vec1->size()==4);

    addr = vec1->at(0);
    assert(addr->ia.sin_family==AF_INET);
    assert(addr->ia.sin_port==htons(6789));
    assert(addr->ia.sin_addr.s_addr==htonl(0xAC1037A0));
    assert(inetAddressToString(addr)=="172.16.55.160:6789");
cout<<'\t'<<inetAddressToString(addr, true)<<endl;

    addr = vec1->at(1);
    assert(addr->ia.sin_family==AF_INET);
    assert(addr->ia.sin_port==htons(555));
    assert(addr->ia.sin_addr.s_addr==htonl(0x7F000001));
    assert(inetAddressToString(addr)=="127.0.0.1:555");
    cout<<'\t'<<inetAddressToString(addr, true)<<endl;

    addr = vec1->at(2);
    assert(addr->ia.sin_family==AF_INET);
    assert(addr->ia.sin_port==htons(1234));
    assert(addr->ia.sin_addr.s_addr==htonl(0x0A0A0C0B));
    assert(inetAddressToString(addr)=="10.10.12.11:1234");
    cout<<'\t'<<inetAddressToString(addr, true)<<endl;

    addr = vec1->at(3);
    assert(addr->ia.sin_family==AF_INET);
    assert(addr->ia.sin_port==htons(555));
    assert(addr->ia.sin_addr.s_addr==htonl(0xC0A80304));
    assert(inetAddressToString(addr)=="192.168.3.4:555");
    cout<<'\t'<<inetAddressToString(addr, true)<<endl;

    cout<<"\nPASSED!\n";

    cout<<"Testing \"ipv4AddressToInt\""<<endl;
    assert(ipv4AddressToInt(*(vec->at(0)))==(int32)0x7F000001);
    assert(ipv4AddressToInt(*(vec->at(1)))==(int32)0x0A0A0C0B);
    assert(ipv4AddressToInt(*(vec->at(2)))==(int32)0xC0A80304);
    cout<<"\nPASSED!\n";

    delete vec;
    delete vec1;

    cout<<"Testing \"intToIPv4Address\""<<endl;
    addr = intToIPv4Address(0x7F000001);
    assert(addr->ia.sin_family==AF_INET);
    assert(inetAddressToString(addr)=="127.0.0.1");
    cout<<'\t'<<inetAddressToString(addr, true)<<endl;
    delete addr;

    addr = intToIPv4Address(0x0A0A0C0B);
    assert(addr->ia.sin_family==AF_INET);
    assert(inetAddressToString(addr)=="10.10.12.11");
    cout<<'\t'<<inetAddressToString(addr, true)<<endl;

    cout<<"\nPASSED!\n";

    cout<<"Testing \"encodeAsIPv6Address\""<<endl;

    ByteBuffer* buff = new ByteBuffer();

    char src[] = { (char)0, (char)0, (char)0, (char)0, (char)0, (char)0,
            (char)0, (char)0, (char)0, (char)0, (char)0xFF, (char)0xFF,
            (char)0x0A, (char)0x0A, (char)0x0C, (char)0x0B };

    encodeAsIPv6Address(buff, addr);
    assert(strncmp(buff->getArray(), src, 16)==0);
    cout<<"\nPASSED!\n";

    // TODO add test for 'getBroadcastAddresses'

    delete addr;

    return 0;
}

