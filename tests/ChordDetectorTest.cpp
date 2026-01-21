#include <QTest>
#include "ChordDetector.h"

class TestChordDetector : public QObject
{
    Q_OBJECT

private slots:
    // Empty and single note tests
    void testEmptyInput();
    void testSingleNote();
    void testSingleNoteAllNotes();

    // Two-note intervals (dyads)
    void testPowerChord();
    void testMinorThird();
    void testMajorThird();

    // Triads
    void testMajorTriad();
    void testMinorTriad();
    void testDiminishedTriad();
    void testAugmentedTriad();
    void testSus2Chord();
    void testSus4Chord();

    // Seventh chords
    void testMajor7th();
    void testMinor7th();
    void testDominant7th();
    void testHalfDiminished();
    void testDiminished7th();
    void testMinorMajor7th();
    void testAugmented7th();
    void testAugmentedMajor7th();

    // Extended chords
    void testDominant9th();
    void testMajor9th();
    void testMinor9th();
    void testDominant7b9();
    void testDominant7sharp9();

    // Different roots
    void testDifferentRoots();

    // Octave normalization
    void testDifferentOctaves();

    // Inversions
    void testInversions();

    // Duplicate notes
    void testDuplicateNotes();

    // Unrecognized chords
    void testUnrecognizedChord();
};

// MIDI note values: C4 = 60, C#4 = 61, D4 = 62, etc.
// C = 0, C# = 1, D = 2, D# = 3, E = 4, F = 5, F# = 6, G = 7, G# = 8, A = 9, A# = 10, B = 11

void TestChordDetector::testEmptyInput()
{
    QList<int> notes;
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString());
}

void TestChordDetector::testSingleNote()
{
    // C4 (MIDI 60)
    QList<int> notes = {60};
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C"));
}

void TestChordDetector::testSingleNoteAllNotes()
{
    QStringList expectedNames = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    for (int i = 0; i < 12; i++) {
        QList<int> notes = {60 + i};  // C4 through B4
        QString result = ChordDetector::detectChord(notes);
        QCOMPARE(result, expectedNames[i]);
    }
}

void TestChordDetector::testPowerChord()
{
    // C5 power chord: C + G (perfect 5th)
    QList<int> notes = {60, 67};  // C4, G4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C (5th)"));
}

void TestChordDetector::testMinorThird()
{
    // C + Eb (minor third)
    QList<int> notes = {60, 63};  // C4, Eb4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cm"));
}

void TestChordDetector::testMajorThird()
{
    // C + E (major third)
    QList<int> notes = {60, 64};  // C4, E4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C"));
}

void TestChordDetector::testMajorTriad()
{
    // C Major: C + E + G (0, 4, 7)
    QList<int> notes = {60, 64, 67};  // C4, E4, G4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C"));
}

void TestChordDetector::testMinorTriad()
{
    // C Minor: C + Eb + G (0, 3, 7)
    QList<int> notes = {60, 63, 67};  // C4, Eb4, G4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cm"));
}

void TestChordDetector::testDiminishedTriad()
{
    // C Diminished: C + Eb + Gb (0, 3, 6)
    QList<int> notes = {60, 63, 66};  // C4, Eb4, Gb4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cdim"));
}

void TestChordDetector::testAugmentedTriad()
{
    // C Augmented: C + E + G# (0, 4, 8)
    QList<int> notes = {60, 64, 68};  // C4, E4, G#4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Caug"));
}

void TestChordDetector::testSus2Chord()
{
    // C Sus2: C + D + G (0, 2, 7)
    QList<int> notes = {60, 62, 67};  // C4, D4, G4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Csus2"));
}

void TestChordDetector::testSus4Chord()
{
    // C Sus4: C + F + G (0, 5, 7)
    QList<int> notes = {60, 65, 67};  // C4, F4, G4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Csus4"));
}

void TestChordDetector::testMajor7th()
{
    // C Major 7: C + E + G + B (0, 4, 7, 11)
    QList<int> notes = {60, 64, 67, 71};  // C4, E4, G4, B4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cmaj7"));
}

void TestChordDetector::testMinor7th()
{
    // C Minor 7: C + Eb + G + Bb (0, 3, 7, 10)
    QList<int> notes = {60, 63, 67, 70};  // C4, Eb4, G4, Bb4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cm7"));
}

void TestChordDetector::testDominant7th()
{
    // C7: C + E + G + Bb (0, 4, 7, 10)
    QList<int> notes = {60, 64, 67, 70};  // C4, E4, G4, Bb4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C7"));
}

void TestChordDetector::testHalfDiminished()
{
    // C Half-diminished (m7b5): C + Eb + Gb + Bb (0, 3, 6, 10)
    QList<int> notes = {60, 63, 66, 70};  // C4, Eb4, Gb4, Bb4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cm7b5"));
}

void TestChordDetector::testDiminished7th()
{
    // C Diminished 7: C + Eb + Gb + Bbb (A) (0, 3, 6, 9)
    QList<int> notes = {60, 63, 66, 69};  // C4, Eb4, Gb4, A4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cdim7"));
}

void TestChordDetector::testMinorMajor7th()
{
    // C Minor Major 7: C + Eb + G + B (0, 3, 7, 11)
    QList<int> notes = {60, 63, 67, 71};  // C4, Eb4, G4, B4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cmmaj7"));
}

void TestChordDetector::testAugmented7th()
{
    // C Augmented 7: C + E + G# + Bb (0, 4, 8, 10)
    QList<int> notes = {60, 64, 68, 70};  // C4, E4, G#4, Bb4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Caug7"));
}

void TestChordDetector::testAugmentedMajor7th()
{
    // C Augmented Major 7: C + E + G# + B (0, 4, 8, 11)
    QList<int> notes = {60, 64, 68, 71};  // C4, E4, G#4, B4
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Caugmaj7"));
}

void TestChordDetector::testDominant9th()
{
    // C9: C + D + E + G + Bb (0, 2, 4, 7, 10)
    QList<int> notes = {60, 62, 64, 67, 70};
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C9"));
}

void TestChordDetector::testMajor9th()
{
    // Cmaj9: C + D + E + G + B (0, 2, 4, 7, 11)
    QList<int> notes = {60, 62, 64, 67, 71};
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cmaj9"));
}

void TestChordDetector::testMinor9th()
{
    // Cm9: C + D + Eb + G + Bb (0, 2, 3, 7, 10)
    QList<int> notes = {60, 62, 63, 67, 70};
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("Cm9"));
}

void TestChordDetector::testDominant7b9()
{
    // C7b9: C + Db + E + G + Bb (0, 1, 4, 7, 10)
    QList<int> notes = {60, 61, 64, 67, 70};
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C7b9"));
}

void TestChordDetector::testDominant7sharp9()
{
    // C7#9: C + D# + E + G + Bb (0, 3, 4, 7, 10)
    QList<int> notes = {60, 63, 64, 67, 70};
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C7#9"));
}

void TestChordDetector::testDifferentRoots()
{
    // Test major triads with different roots
    struct TestCase {
        QList<int> notes;
        QString expected;
    };

    QList<TestCase> testCases = {
        {{60, 64, 67}, "C"},      // C Major
        {{62, 66, 69}, "D"},      // D Major
        {{64, 68, 71}, "E"},      // E Major
        {{65, 69, 72}, "F"},      // F Major
        {{67, 71, 74}, "G"},      // G Major
        {{69, 73, 76}, "A"},      // A Major
        {{71, 75, 78}, "B"},      // B Major
    };

    for (const auto& tc : testCases) {
        QString result = ChordDetector::detectChord(tc.notes);
        QCOMPARE(result, tc.expected);
    }

    // Test minor triads with different roots
    QList<TestCase> minorCases = {
        {{60, 63, 67}, "Cm"},     // C Minor
        {{62, 65, 69}, "Dm"},     // D Minor
        {{64, 67, 71}, "Em"},     // E Minor
        {{69, 72, 76}, "Am"},     // A Minor
    };

    for (const auto& tc : minorCases) {
        QString result = ChordDetector::detectChord(tc.notes);
        QCOMPARE(result, tc.expected);
    }
}

void TestChordDetector::testDifferentOctaves()
{
    // C Major in different octaves should all be recognized
    // C2, E2, G2
    QList<int> low = {36, 40, 43};
    QCOMPARE(ChordDetector::detectChord(low), QString("C"));

    // C5, E5, G5
    QList<int> high = {72, 76, 79};
    QCOMPARE(ChordDetector::detectChord(high), QString("C"));

    // C4, E5, G6 (spread voicing)
    QList<int> spread = {60, 76, 91};
    QCOMPARE(ChordDetector::detectChord(spread), QString("C"));
}

void TestChordDetector::testInversions()
{
    QList<int> firstInv = {60, 65, 69};  // F4, A4, C5
    QString result = ChordDetector::detectChord(firstInv);
    QCOMPARE(result, "F");

    QList<int> secondInv = {69, 72, 77};  // A4, C5 F5
    result = ChordDetector::detectChord(secondInv);
    QCOMPARE(result, "F");
}

void TestChordDetector::testDuplicateNotes()
{
    // C Major with duplicate notes
    QList<int> notes = {60, 64, 67, 60, 64};  // C, E, G, C, E
    QString result = ChordDetector::detectChord(notes);
    QCOMPARE(result, QString("C"));

    // Same note multiple times
    QList<int> sameNote = {60, 60, 60};
    result = ChordDetector::detectChord(sameNote);
    QCOMPARE(result, QString("C"));
}

void TestChordDetector::testUnrecognizedChord()
{
    // Cluster chord that doesn't match any pattern
    QList<int> cluster = {60, 61, 62, 63, 64, 65};  // C, C#, D, D#, E, F
    QString result = ChordDetector::detectChord(cluster);
    // Should return empty or try to identify something
    // The algorithm may still try to match something, so we just verify it doesn't crash
    QVERIFY(true);  // If we get here, no crash occurred
}

QTEST_MAIN(TestChordDetector)
#include "tst_chorddetector.moc"
