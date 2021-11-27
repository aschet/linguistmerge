// Copyright 2021 Thomas Ascher
// SPDX-License-Identifier: GPL-3.0-or-later

#include <ts.h>
#include <tsreader.h>
#include <tswriter.h>
#include <QtTest>

class LinguistMergeTest : public QObject
{
    Q_OBJECT
public:
    LinguistMergeTest();

private:
    Q_SLOT void initTestCase();

    Q_SLOT void cleanupTestCase();

    Q_SLOT void test_read();

    Q_SLOT void test_write();

    Q_SLOT void test_merge();

private:
    void readTS(TS &ts, const QString &input);

    void readTS(TS &ts);

    void verifyRead(TS &ts);

    const QString m_tsInput;
};

LinguistMergeTest::LinguistMergeTest()
    :m_tsInput(R"(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="pl_PL" sourcelanguage="en_US">
<context>
    <name>Widget1</name>
    <message>
        <location filename="../ui/widget1.ui" line="10"/>
        <source>test 1</source>
        <translatorcomment>Google Translate</translatorcomment>
        <translation>test 1</translation>
    </message>
    <message>
        <location filename="../ui/widget1.ui" line="20"/>
        <location filename="../ui/widget1.ui" line="30"/>
        <source>test 2</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Widget2</name>
    <message numerus="yes">
        <location filename="../ui/widget2.ui" line="10"/>
        <source>%n tests</source>
        <translation type="unfinished">
            <numerusform>%n test</numerusform>
            <numerusform></numerusform>
            <numerusform>%n testy</numerusform>
        </translation>
    </message>
    <message>
        <location filename="../ui/widget2.ui" line="20"/>
        <source>test 1</source>
        <translation type="obsolete">test 1</translation>
    </message>
</context>
</TS>)")
{
}

void LinguistMergeTest::initTestCase()
{

}

void LinguistMergeTest::cleanupTestCase()
{

}

void LinguistMergeTest::test_read()
{
    TS ts;
    readTS(ts);
    verifyRead(ts);
}

void LinguistMergeTest::test_write()
{
    TS ts;
    readTS(ts);

    QString tsOutput;
    {
        TSWriter writer(&tsOutput);
        writer.write(&ts);

        TSWriter::write("/home/tascher/out.xml", &ts);
    }

    ts = TS();
    readTS(ts, tsOutput);
    verifyRead(ts);
}

void LinguistMergeTest::test_merge()
{
    Message messageA;
    messageA.setSource("Hello");
    messageA.translations().append(QString());

    Message messageB = messageA;
    messageB.setType(Message::Finished);
    messageB.translations()[0] = "Ola";

    Context contextA1;
    contextA1.setName("Test1");
    contextA1.addMessage(messageA);

    Context contextB1;
    contextB1.setName(contextA1.getName());
    contextB1.addMessage(messageB);

    Context contextB2;
    contextB2.setName("Test2");
    contextB2.addMessage(messageA);

    TS tsA;
    TS tsB;
    tsA.addContext(contextA1);
    tsB.addContext(contextB1);
    tsB.addContext(contextB2);

    TS tsAB;
    tsAB.merge(tsA);
    tsAB.merge(tsB);

    const Context* mergedContext = tsAB.findContext(contextA1.getName());
    QVERIFY(mergedContext != nullptr);
    QVERIFY(tsAB.findContext(contextB2.getName()) != nullptr);

    if (mergedContext)
    {
        const Message* mergedMessage = mergedContext->findMessage(messageB.getSource());
        QVERIFY(mergedMessage != nullptr);
        if (mergedMessage)
            QVERIFY(messageB == *mergedMessage);
    }
}

void LinguistMergeTest::readTS(TS &ts, const QString &input)
{
    TSReader reader(input);
    reader.read(&ts);
}

void LinguistMergeTest::readTS(TS &ts)
{
    readTS(ts, m_tsInput);
}

void LinguistMergeTest::verifyRead(TS &ts)
{
    QCOMPARE("pl_PL", ts.getLanguage());
    QCOMPARE("en_US", ts.getSourceLanguage());

    const Context *widget1 = ts.findContext("Widget1");
    QVERIFY(widget1 != nullptr);

    const Context *widget2 = ts.findContext("Widget2");
    QVERIFY(widget2 != nullptr);

    const Message* widget1Message1 = widget1->findMessage("test 1");
    QVERIFY(widget1Message1 != nullptr);

    if (widget1Message1)
    {
        Message widget1Message1Exp;
        widget1Message1Exp.setType(Message::Finished);
        widget1Message1Exp.setSource("test 1");
        widget1Message1Exp.locations().append(Location("../ui/widget1.ui", 10));
        widget1Message1Exp.setTranslatorComment("Google Translate");
        widget1Message1Exp.translations().append("test 1");
        QVERIFY(widget1Message1Exp == *widget1Message1);
    }
}

#include "tst_linguistmerge.moc"

QTEST_APPLESS_MAIN(LinguistMergeTest)
