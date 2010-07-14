///////////////////////////////////////////////////////////////////////////////
// Name:        tests/controls/radioboxtest.cpp
// Purpose:     wxRadioBox unit test
// Author:      Steven Lamerton
// Created:     2010-07-14
// RCS-ID:      $Id$
// Copyright:   (c) 2010 Steven Lamerton
///////////////////////////////////////////////////////////////////////////////

#include "testprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/app.h"
    #include "wx/radiobox.h"
#endif // WX_PRECOMP

class RadioBoxTestCase : public CppUnit::TestCase
{
public:
    RadioBoxTestCase() { }

    void setUp();
    void tearDown();

private:
    CPPUNIT_TEST_SUITE( RadioBoxTestCase );
        CPPUNIT_TEST( FindString );
        CPPUNIT_TEST( RowColCount );
        CPPUNIT_TEST( Enable );
        CPPUNIT_TEST( Show );
        CPPUNIT_TEST( HelpText );
    CPPUNIT_TEST_SUITE_END();

    void FindString();
    void RowColCount();
    void Enable();
    void Show();
    void HelpText();

    wxRadioBox* m_radio;

    DECLARE_NO_COPY_CLASS(RadioBoxTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( RadioBoxTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( RadioBoxTestCase, "RadioBoxTestCase" );

void RadioBoxTestCase::setUp()
{
    wxArrayString choices;
    choices.push_back("item 0");
    choices.push_back("item 1");
    choices.push_back("item 2");

    m_radio = new wxRadioBox(wxTheApp->GetTopWindow(), wxID_ANY, "RadioBox",
                             wxDefaultPosition, wxDefaultSize, choices);
}

void RadioBoxTestCase::tearDown()
{
    wxDELETE(m_radio);
}

void RadioBoxTestCase::FindString()
{
    CPPUNIT_ASSERT_EQUAL(wxNOT_FOUND, m_radio->FindString("not here"));
    CPPUNIT_ASSERT_EQUAL(1, m_radio->FindString("item 1"));
    CPPUNIT_ASSERT_EQUAL(2, m_radio->FindString("ITEM 2"));
    CPPUNIT_ASSERT_EQUAL(wxNOT_FOUND, m_radio->FindString("ITEM 2", true));
}

void RadioBoxTestCase::RowColCount()
{
    wxArrayString choices;
    choices.push_back("item 0");
    choices.push_back("item 1");
    choices.push_back("item 2");

    m_radio = new wxRadioBox(wxTheApp->GetTopWindow(), wxID_ANY, "RadioBox",
                             wxDefaultPosition, wxDefaultSize, choices, 2);

    CPPUNIT_ASSERT_EQUAL(2, m_radio->GetColumnCount());
    CPPUNIT_ASSERT_EQUAL(2, m_radio->GetRowCount());

    m_radio = new wxRadioBox(wxTheApp->GetTopWindow(), wxID_ANY, "RadioBox",
                             wxDefaultPosition, wxDefaultSize, choices, 1, 
                             wxRA_SPECIFY_ROWS);

    CPPUNIT_ASSERT_EQUAL(3, m_radio->GetColumnCount());
    CPPUNIT_ASSERT_EQUAL(1, m_radio->GetRowCount());
}

void RadioBoxTestCase::Enable()
{
    m_radio->Enable(false);

    CPPUNIT_ASSERT(!m_radio->IsItemEnabled(0));

    m_radio->Enable(1, true);

    CPPUNIT_ASSERT(!m_radio->IsItemEnabled(0));
    CPPUNIT_ASSERT(m_radio->IsItemEnabled(1));
    CPPUNIT_ASSERT(!m_radio->IsItemEnabled(2));

    m_radio->Enable(true);

    CPPUNIT_ASSERT(m_radio->IsItemEnabled(0));
    CPPUNIT_ASSERT(m_radio->IsItemEnabled(1));
    CPPUNIT_ASSERT(m_radio->IsItemEnabled(2));

    m_radio->Enable(0, false);

    CPPUNIT_ASSERT(!m_radio->IsItemEnabled(0));
    CPPUNIT_ASSERT(m_radio->IsItemEnabled(1));
    CPPUNIT_ASSERT(m_radio->IsItemEnabled(2));
}

void RadioBoxTestCase::Show()
{
    m_radio->Show(false);

    CPPUNIT_ASSERT(!m_radio->IsItemShown(0));

    m_radio->Show(1, true);

    CPPUNIT_ASSERT(!m_radio->IsItemShown(0));
    CPPUNIT_ASSERT(m_radio->IsItemShown(1));
    CPPUNIT_ASSERT(!m_radio->IsItemShown(2));

    m_radio->Show(true);

    CPPUNIT_ASSERT(m_radio->IsItemShown(0));
    CPPUNIT_ASSERT(m_radio->IsItemShown(1));
    CPPUNIT_ASSERT(m_radio->IsItemShown(2));

    m_radio->Show(0, false);

    CPPUNIT_ASSERT(!m_radio->IsItemShown(0));
    CPPUNIT_ASSERT(m_radio->IsItemShown(1));
    CPPUNIT_ASSERT(m_radio->IsItemShown(2));
}

void RadioBoxTestCase::HelpText()
{
    CPPUNIT_ASSERT_EQUAL(wxEmptyString, m_radio->GetItemHelpText(0));

    m_radio->SetItemHelpText(1, "Item 1 help");

    CPPUNIT_ASSERT_EQUAL("Item 1 help", m_radio->GetItemHelpText(1));

    m_radio->SetItemHelpText(1, "");

    CPPUNIT_ASSERT_EQUAL(wxEmptyString, m_radio->GetItemHelpText(1));
}
