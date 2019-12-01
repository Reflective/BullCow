// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

// initializes gameover state and prompts player
void UBullCowCartridge::SetupGame()
{
    bGameOver = false;
    // Set Hidden word to a random 4 - 8 character Isogram within a TArray 
    HiddenWord = GetValidWords(WordList)[FMath::RandRange(0, GetValidWords(WordList).Num() - 1)];
    Lives = HiddenWord.Len();
    //Display Info and prompt input
    PrintLine(TEXT("The number of words is %i"), WordList.Num());
    PrintLine(TEXT("The number of valid words is: %i"), GetValidWords(WordList).Num());
    PrintLine(FString::Printf(TEXT("The Hidden word is: %s"), HiddenWord));
    PrintLine(TEXT("   Welcome to Salby McCorns Home for cows"));
    PrintLine(FString::Printf(TEXT("             You have %i Tries to\n            Guess the %i letter word"), HiddenWord.Len(), HiddenWord.Len()));
    PrintLine(TEXT("              Type in your guess"));
    PrintLine(TEXT("         and press ENTER to continue..."));
}
 
// ends game and prompts to play again
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("                Press ENTER to Play again "));
} 

// Determine if guess is correct and display if it is or isnt
void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    //check correct
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You Win!"));
        EndGame();
        return;
    }
    //check length
    if (HiddenWord.Len() != Guess.Len())
    {
        PrintLine(FString::Printf(TEXT("        The hidden word is %i letters long!"), HiddenWord.Len()));
        PrintLine(TEXT("               You have %i Tries left"), Lives);
        PrintLine(TEXT("                  Type in your guess"));
        PrintLine(TEXT("              Press ENTER to try again..."));
        return;
    }
    // check !Isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("        No repeating letters, guess again."));
        return;
    }
    // remove life
    else 
    {
        PrintLine(TEXT("You lost a life"));
        --Lives;
    // check game over
        if (Lives <= 0)
        {
            PrintLine(TEXT("                   GAME OVER"));
            PrintLine(TEXT(" "));
            EndGame();
        }
        else // prompt retry
        {
            PrintLine(TEXT("               You have %i Tries left"), Lives);
            PrintLine(TEXT("                  Type in your guess"));
            PrintLine(TEXT("              Press ENTER to try again..."));
        }
    }
}

// check if string is isogram
bool UBullCowCartridge::IsIsogram(const FString &Word) const
{
    for (size_t Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

// Creates new TArray storing words filtered from WordList
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& List) const
{
    TArray<FString> ValidWords;
    for (FString Check : List)
    {
        if (Check.Len() >= 4 && Check.Len() <= 8 && IsIsogram(Check))
        {
            ValidWords.Emplace(Check);
        }
    }
    return ValidWords;
}

// TArray<FString> UBullCowCartridge::RandomList(const TArray<FString>& List) const
// {
//     FMath::RandRange(0, 10);
// }
