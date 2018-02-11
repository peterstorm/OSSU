// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include <math.h>
#define A4      10

                        


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // we have to separete the numerator and denominator from each other,
    // so we use strtok to find the first character of the string, and delimit 
    // using "/".
    int numerator = atoi(strtok(fraction, "/"));
    // the function replaces chosen delimeter with a NULL character. Because strtok
    // maintains internal space, and actually modifies the original string,
    // we can call with NULL again, to start from there.
    int denominator = atoi(strtok(NULL, fraction));
    // then we cast to float, because I can't figure out how to do fractions.
    // We divide, and multiply by 8 to get the number of "eihts".
    float eights = ((float)numerator / (float)denominator) * 8;
    return (int)eights;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // I am not proud of this solution, but it works...
    // First I make two arrays consisting of every posible note, one with sharp and one flat
    const string NOTESSHARP[] = {"C","C#", "D","D#", "E", "F",
                        "F#","G","G#", "A","A#", "B"
                       };
    const string NOTESFLAT[] = {"C","Db", "D","Eb", "E", "F",
                        "Gb","G","Ab", "A","Bb", "B"
                       };
    // declare varibles
    float frequencyFloat;
    int frequency;
    int octave;
    int notePosition = 0;
    int semiTones = 0;
    float power;
    int moveOctave;
    
    // if the length of note is 3, I know it has an accidental.
    if(strlen(note) == 3)
    {
        // I then save the octave as an int with atoi and put a null terminator
        // so I can do strcmp on it.
        octave = atoi(&note[2]);
        note[2] = '\0';
        // if its sharp, I iterate through the array with sharp notes, and save
        // the position as notePosition.
        if(note[1] == '#')
        {
            for(int i = 0; i < 12; i++)
            {
                if(strcmp(NOTESSHARP[i], note) == 0)
                {
                    notePosition = i + 1;
                    break;
                }
            }
        }
        // same thing if it's flat.
        else if(note[1] == 'b')
        {
            for(int i = 0; i < 12; i++)
            {
                if(strcmp(NOTESFLAT[i], note) == 0)
                {
                    notePosition = i + 1;
                    break;
                }
            }
        }
    }
    // if the note does not contain an accidental, we do the same as with one.
    else
    {
        octave = atoi(&note[1]);
        note[1] = '\0';
        for(int i = 0; i < 12; i++)
        {
            if(strcmp(NOTESSHARP[i], note) == 0)
            {
                notePosition = i + 1;
                break;
            }
        }
    }
    // then we find the number of semitones away from A4.
    if(notePosition < A4 || notePosition > A4)
    {
        semiTones = notePosition - A4;
    }
    else if(notePosition == A4)
    {
        semiTones = 0;
    }

    // then we calculate the frequency using 2^(semiTones / 12) * 440 (A4).
    power = (float)semiTones / 12;
    frequencyFloat = round(pow(2,power) * 440);
    // then we check for the octave, and calcuate the frequency change.
    if(octave < 4)
    {
        moveOctave = (4 - octave);
        frequencyFloat = frequencyFloat / pow(2,moveOctave);
    }
    else if(octave > 4)
    {
        moveOctave = (octave - 4);
        frequencyFloat = frequencyFloat * pow(2,moveOctave);
    }
    frequency = (int)frequencyFloat;
    return frequency;  
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // We know from the documentation that if the user inputs a '\n' into get_string
    // the get_string function will return "".
    // The function has to return true if a line has been input, and false if not.
    if(strcmp(s,"") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
