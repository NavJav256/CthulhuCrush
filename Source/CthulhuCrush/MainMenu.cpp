// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"

bool UMainMenu::Initialize()
{
	if(!Super::Initialize()) return false;

	ProfileNum = FMath::RandRange(0, 4);
	CorrectAnswer = Profiles[ProfileNum].Name;

	CreateTraitPool();

	SelectCharacterTraits();

	if (PlayButton)
	{
		PlayButton->OnPressed.AddDynamic(this, &UMainMenu::PlayButtonPressed);
		PlayButton->OnHovered.AddDynamic(this, &UMainMenu::HoverPlayButton);
		PlayButton->OnUnhovered.AddDynamic(this, &UMainMenu::UnHoverPlayButton);
	}
	if (ExitButton)
	{
		ExitButton->OnHovered.AddDynamic(this, &UMainMenu::HoverExitButton);
		ExitButton->OnUnhovered.AddDynamic(this, &UMainMenu::UnHoverExitButton);
	}
	if (GalleryButton)
	{
		GalleryButton->OnPressed.AddDynamic(this, &UMainMenu::GalleryButtonPressed);
	}
	if (CharacterButton)
	{
		CharacterButton->OnPressed.AddDynamic(this, &UMainMenu::CharacterButtonPressed);
	}
	if (SearchButton)
	{
		SearchButton->OnPressed.AddDynamic(this, &UMainMenu::SearchButtonPressed);
	}
	if (SocialButton)
	{
		SocialButton->OnPressed.AddDynamic(this, &UMainMenu::SocialButtonPressed);
	}
	if (DictionaryButton)
	{
		DictionaryButton->OnPressed.AddDynamic(this, &UMainMenu::DictionaryButtonPressed);
	}
	if (HandbookButton)
	{
		HandbookButton->OnPressed.AddDynamic(this, &UMainMenu::HandbookButtonPressed);
	}
	if (PestilenceButton)
	{
		PestilenceButton->OnPressed.AddDynamic(this, &UMainMenu::PestilenceButtonPressed);
	}
	if (WidowButton)
	{
		WidowButton->OnPressed.AddDynamic(this, &UMainMenu::WidowButtonPressed);
	}
	if (GruudButton)
	{
		GruudButton->OnPressed.AddDynamic(this, &UMainMenu::GruudButtonPressed);
	}
	if (BigTreeButton)
	{
		BigTreeButton->OnPressed.AddDynamic(this, &UMainMenu::BigTreeButtonPressed);
	}
	if (CthulhuButton)
	{
		CthulhuButton->OnPressed.AddDynamic(this, &UMainMenu::CthulhuButtonPressed);
	}
	if (ConfirmButton)
	{
		ConfirmButton->OnPressed.AddDynamic(this, &UMainMenu::ConfirmButtonPressed);
		ConfirmButton->OnHovered.AddDynamic(this, &UMainMenu::HoverConfirmButton);
		ConfirmButton->OnUnhovered.AddDynamic(this, &UMainMenu::UnHoverConfirmButton);
	}
	return true;
}

void UMainMenu::CreateTraitPool()
{
	TraitPool.Empty();
	for (auto Trait : Traits)
	{
		if (!Trait.Disqualifies.Contains(CorrectAnswer))
		{
			TraitPool.Add(Trait);
		}
	}
}

void UMainMenu::SelectCharacterTraits()
{
	ShuffleArray(TraitPool);
	TArray<FTrait> RemainingTraits = TraitPool;

	TArray<int32> ProfileNums { 0, 1, 2, 3, 4 };
	ProfileNums.Remove(ProfileNum);
	TArray<FString> ProfileNames;

	for (int32 Num : ProfileNums)
	{
		ProfileNames.Add(Profiles[Num].Name);
	}

	for (FString ProfileName : ProfileNames)
	{
		for (int32 i = 0; i < RemainingTraits.Num(); i++)
		{
			if (RemainingTraits[i].Disqualifies.Contains(ProfileName))
			{
				RemainingTraits[i].bOwning = true;
				OwningTraits.Add(RemainingTraits[i]);
				RemainingTraits.RemoveAt(i);
				break;
			}
		}
	}
	
	while (OwningTraits.Num() < NumOfOwningTraits && RemainingTraits.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, RemainingTraits.Num() - 1);
		RemainingTraits[Index].bOwning = true;
		OwningTraits.Add(RemainingTraits[Index]);
		RemainingTraits.RemoveAt(Index);
	}
	
	for (auto T : OwningTraits)
	{
		UTextBlock* NewTraitText = NewObject<UTextBlock>(TraitsBox);
		if (NewTraitText)
		{
			NewTraitText->SetAutoWrapText(true);
			FSlateFontInfo FontInfo = NewTraitText->GetFont();
			FontInfo.Size = 18;
			NewTraitText->SetFont(FontInfo);
			NewTraitText->SetText(FText::FromString(T.TraitName));
			TraitsBox->AddChild(NewTraitText);
		}

		USizeBox* NewTraitSpacer = NewObject<USizeBox>(TraitsBox);
		if (NewTraitSpacer)
		{
			NewTraitSpacer->SetMinDesiredHeight(TraitSpacer);
			TraitsBox->AddChild(NewTraitSpacer);
		}
	}
}

void UMainMenu::ShuffleArray(TArray<FTrait> &Array)
{
	for (int32 i = Array.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::RandRange(0, i);
		if (i != j)
		{
			Array.Swap(i, j);
		}
	}
}

void UMainMenu::Setup()
{
	AddToViewport();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

void UMainMenu::PlayButtonPressed()
{
	if (Game)
	{
		SwitchMenu(Game);
	}
}

void UMainMenu::SwitchMenu(UWidget* Menu)
{
	if (MenuSwitcher)
	{
		MenuSwitcher->SetActiveWidget(Menu);
	}
}

void UMainMenu::SwitchGameMenu(UWidget* Menu)
{
	if (GameSwitcher)
	{
		GameSwitcher->SetActiveWidget(Menu);
	}
}

void UMainMenu::HoverPlayButton()
{
	if (PlayText)
	{
		IncreaseTextSize(PlayText);
	}
}

void UMainMenu::UnHoverPlayButton()
{
	if (PlayText)
	{
		DecreaseTextSize(PlayText);
	}
}

void UMainMenu::HoverExitButton()
{
	if (ExitText)
	{
		IncreaseTextSize(ExitText);
	}
}

void UMainMenu::UnHoverExitButton()
{
	if (ExitText)
	{
		DecreaseTextSize(ExitText);
	}
}

void UMainMenu::ConfirmButtonPressed()
{
	if (EndScreenText)
	{
		FString EndText;
		if (SelectedAnswer.Equals(CorrectAnswer))
		{
			EndText = TEXT("Congratulations! You are now a follower!");
		}
		else
		{
			EndText = TEXT("Unfortunately, you have been deemed unworthy!\nYou are to be sacrificed!");
		}
		EndScreenText->SetText(FText::FromString(EndText));
	}
	if (EndScreen)
	{
		SwitchGameMenu(EndScreen);
	}

}

void UMainMenu::HoverConfirmButton()
{
	if (ConfirmText)
	{
		IncreaseTextSize(ConfirmText);
	}
}

void UMainMenu::UnHoverConfirmButton()
{
	if (ConfirmText)
	{
		DecreaseTextSize(ConfirmText);
	}
}

void UMainMenu::IncreaseTextSize(UTextBlock* Text)
{
	FSlateFontInfo FontInfo = Text->GetFont();
	FontInfo.Size += 4;
	Text->SetFont(FontInfo);
}

void UMainMenu::DecreaseTextSize(UTextBlock* Text)
{
	FSlateFontInfo FontInfo = Text->GetFont();
	FontInfo.Size -= 4;
	Text->SetFont(FontInfo);
}

void UMainMenu::GalleryButtonPressed()
{
	if (GalleryScreen)
	{
		SwitchGameMenu(GalleryScreen);
	}
}

void UMainMenu::CharacterButtonPressed()
{
	if (CharacterScreen)
	{
		SwitchGameMenu(CharacterScreen);
	}
}

void UMainMenu::SearchButtonPressed()
{
	if (!DisabledButtons)
	{
		if (SearchScreen)
		{
			SwitchGameMenu(SearchScreen);
		}
	}
}

void UMainMenu::SocialButtonPressed()
{
	if (!DisabledButtons)
	{
		if (SocialScreen)
		{
			SwitchGameMenu(SocialScreen);
		}
	}
}

void UMainMenu::DictionaryButtonPressed()
{
	if (DictionaryScreen)
	{
		SwitchGameMenu(DictionaryScreen);
	}
}

void UMainMenu::HandbookButtonPressed()
{

	if (HandbookScreen)
	{
		SwitchGameMenu(HandbookScreen);
	}
}

void UMainMenu::PestilenceButtonPressed()
{
	if (DisabledButtons)
	{
		DisabledButtons = false;
	}

	if (ProfileScreen)
	{
		bool Valid =
			EndProfileImage && 
			ProfileImage &&
			SelectedProfileImage &&
			SelectedNameText &&
			NameText &&
			HeightText &&
			WeightText &&
			RaceText &&
			HobbiesText &&
			SearchResultText &&
			SearchTextOne &&
			SearchTextTwo &&
			SearchTextThree &&
			SearchTextFour && 
			DBText;

		if (Valid && !Profiles.IsEmpty())
		{
			NameText->SetText(FText::FromString(Profiles[0].Name));
			HeightText->SetText(FText::FromString(Profiles[0].Height));
			WeightText->SetText(FText::FromString(Profiles[0].Weight));
			RaceText->SetText(FText::FromString(Profiles[0].Race));
			ProfileImage->SetBrushFromTexture(Profiles[0].ProfilePic);
			SelectedProfileImage->SetBrushFromTexture(Profiles[0].ProfilePic);
			EndProfileImage->SetBrushFromTexture(Profiles[0].ProfilePic);
			SelectedNameText->SetText(FText::FromString(Profiles[0].Name));
			CultSign->SetBrushFromTexture(Profiles[0].CultSign);
			SearchResultText->SetText(FText::FromString(Profiles[0].Name));
			SearchTextOne->SetText(FText::FromString(Profiles[0].SearchResults[0]));
			SearchTextTwo->SetText(FText::FromString(Profiles[0].SearchResults[1]));
			SearchTextThree->SetText(FText::FromString(Profiles[0].SearchResults[2]));
			SearchTextFour->SetText(FText::FromString(Profiles[0].SearchResults[3]));

			if (BioBox)
			{
				BioBox->ClearChildren();
				for (auto Line : Profiles[0].Bio)
				{
					UTextBlock* NewBioLine = NewObject<UTextBlock>(BioBox);
					if (NewBioLine)
					{
						NewBioLine->SetAutoWrapText(true);
						FSlateFontInfo FontInfo = NewBioLine->GetFont();
						FontInfo.Size = 16;
						NewBioLine->SetFont(FontInfo);
						NewBioLine->SetText(FText::FromString(Line));
						BioBox->AddChild(NewBioLine);
					}

					USizeBox* NewLineSpacer = NewObject<USizeBox>(BioBox);
					if (NewLineSpacer)
					{
						NewLineSpacer->SetMinDesiredHeight(BioSpacer);
						BioBox->AddChild(NewLineSpacer);
					}
				}

			}
			
			FString Hobbies;
			FString DBs;
			Hobbies.Append(TEXT("Hobbies: \n"));
			DBs.Append(TEXT("Dealbreakers: \n"));
			for (FString Hobby : Profiles[0].Hobbies)
			{
				Hobbies.Append(Hobby);
				Hobbies.Append(TEXT("\n"));
			}
			for (FString DB : Profiles[0].DealBreakers)
			{
				DBs.Append(DB);
				DBs.Append(TEXT("\n"));
			}
			HobbiesText->SetText(FText::FromString(Hobbies));
			DBText->SetText(FText::FromString(DBs));
			
		}

		if (FeedBox)
		{
			FeedBox->ClearChildren();
			for (auto Item : Profiles[0].Feed)
			{
				UTextBlock* NewPostText = NewObject<UTextBlock>(FeedBox);
				if (NewPostText)
				{
					NewPostText->SetAutoWrapText(true);
					NewPostText->SetText(FText::FromString(Item.Post));
					FeedBox->AddChild(NewPostText);
				}

				USizeBox* NewPostSpacer = NewObject<USizeBox>(FeedBox);
				if (NewPostSpacer)
				{
					NewPostSpacer->SetMinDesiredHeight(PostSpacer);
					FeedBox->AddChild(NewPostSpacer);
				}

				for (auto Comment : Item.Comments)
				{
					UTextBlock* NewCommentText = NewObject<UTextBlock>(FeedBox);
					if (NewCommentText)
					{
						NewCommentText->SetAutoWrapText(true);
						NewCommentText->SetText(FText::FromString(Comment));
						FeedBox->AddChild(NewCommentText);
					}

					USizeBox* NewCommentSpacer = NewObject<USizeBox>(FeedBox);
					NewCommentSpacer->SetMinDesiredHeight(CommentSpacer);
					if (NewCommentSpacer)
					{
						FeedBox->AddChild(NewCommentSpacer);
					}
				}

				if (Profiles[0].Feed.Num() > 1)
				{
					USizeBox* NewSeparator = NewObject<USizeBox>(FeedBox);
					if (NewSeparator)
					{
						NewSeparator->SetMinDesiredHeight(SeparatorSpace);
						FeedBox->AddChild(NewSeparator);
					}
				}
			}
		}
		
		SwitchGameMenu(ProfileScreen);
	}
}

void UMainMenu::WidowButtonPressed()
{
	if (DisabledButtons)
	{
		DisabledButtons = false;
	}

	if (ProfileScreen)
	{
		bool Valid =
			EndProfileImage &&
			ProfileImage &&
			SelectedProfileImage &&
			SelectedNameText &&
			NameText &&
			HeightText &&
			WeightText &&
			RaceText &&
			HobbiesText &&
			SearchResultText &&
			SearchTextOne &&
			SearchTextTwo &&
			SearchTextThree &&
			SearchTextFour &&
			DBText;

		if (Valid && !Profiles.IsEmpty())
		{
			NameText->SetText(FText::FromString(Profiles[1].Name));
			HeightText->SetText(FText::FromString(Profiles[1].Height));
			WeightText->SetText(FText::FromString(Profiles[1].Weight));
			RaceText->SetText(FText::FromString(Profiles[1].Race));
			ProfileImage->SetBrushFromTexture(Profiles[1].ProfilePic);
			SelectedProfileImage->SetBrushFromTexture(Profiles[1].ProfilePic);
			EndProfileImage->SetBrushFromTexture(Profiles[1].ProfilePic);
			SelectedNameText->SetText(FText::FromString(Profiles[1].Name));
			CultSign->SetBrushFromTexture(Profiles[1].CultSign);
			SearchResultText->SetText(FText::FromString(Profiles[1].Name));
			SearchTextOne->SetText(FText::FromString(Profiles[1].SearchResults[0]));
			SearchTextTwo->SetText(FText::FromString(Profiles[1].SearchResults[1]));
			SearchTextThree->SetText(FText::FromString(Profiles[1].SearchResults[2]));
			SearchTextFour->SetText(FText::FromString(Profiles[1].SearchResults[3]));

			if (BioBox)
			{
				BioBox->ClearChildren();
				for (auto Line : Profiles[1].Bio)
				{
					UTextBlock* NewBioLine = NewObject<UTextBlock>(BioBox);
					if (NewBioLine)
					{
						NewBioLine->SetAutoWrapText(true);
						FSlateFontInfo FontInfo = NewBioLine->GetFont();
						FontInfo.Size = 16;
						NewBioLine->SetFont(FontInfo);
						NewBioLine->SetText(FText::FromString(Line));
						BioBox->AddChild(NewBioLine);
					}

					USizeBox* NewLineSpacer = NewObject<USizeBox>(BioBox);
					if (NewLineSpacer)
					{
						NewLineSpacer->SetMinDesiredHeight(BioSpacer);
						BioBox->AddChild(NewLineSpacer);
					}
				}

			}
			
			FString Hobbies;
			FString DBs;
			Hobbies.Append(TEXT("Hobbies: \n"));
			DBs.Append(TEXT("Dealbreakers: \n"));
			for (FString Hobby : Profiles[1].Hobbies)
			{
				Hobbies.Append(Hobby);
				Hobbies.Append(TEXT("\n"));
			}
			for (FString DB : Profiles[1].DealBreakers)
			{
				DBs.Append(DB);
				DBs.Append(TEXT("\n"));
			}
			HobbiesText->SetText(FText::FromString(Hobbies));
			DBText->SetText(FText::FromString(DBs));
		}

		if (FeedBox)
		{
			FeedBox->ClearChildren();
			for (auto Item : Profiles[1].Feed)
			{
				UTextBlock* NewPostText = NewObject<UTextBlock>(FeedBox);
				if (NewPostText)
				{
					NewPostText->SetAutoWrapText(true);
					NewPostText->SetText(FText::FromString(Item.Post));
					FeedBox->AddChild(NewPostText);
				}

				USizeBox* NewPostSpacer = NewObject<USizeBox>(FeedBox);
				if (NewPostSpacer)
				{
					NewPostSpacer->SetMinDesiredHeight(PostSpacer);
					FeedBox->AddChild(NewPostSpacer);
				}

				for (auto Comment : Item.Comments)
				{
					UTextBlock* NewCommentText = NewObject<UTextBlock>(FeedBox);
					if (NewCommentText)
					{
						NewCommentText->SetAutoWrapText(true);
						NewCommentText->SetText(FText::FromString(Comment));
						FeedBox->AddChild(NewCommentText);
					}

					USizeBox* NewCommentSpacer = NewObject<USizeBox>(FeedBox);
					NewCommentSpacer->SetMinDesiredHeight(CommentSpacer);
					if (NewCommentSpacer)
					{
						FeedBox->AddChild(NewCommentSpacer);
					}
				}

				if (Profiles[1].Feed.Num() > 1)
				{
					USizeBox* NewSeparator = NewObject<USizeBox>(FeedBox);
					if (NewSeparator)
					{
						NewSeparator->SetMinDesiredHeight(SeparatorSpace);
						FeedBox->AddChild(NewSeparator);
					}
				}
			}
		}

		SwitchGameMenu(ProfileScreen);
	}
}

void UMainMenu::GruudButtonPressed()
{
	if (DisabledButtons)
	{
		DisabledButtons = false;
	}

	if (ProfileScreen)
	{
		bool Valid =
			EndProfileImage &&
			ProfileImage &&
			SelectedProfileImage &&
			SelectedNameText &&
			NameText &&
			HeightText &&
			WeightText &&
			RaceText &&
			HobbiesText &&
			SearchResultText &&
			SearchTextOne &&
			SearchTextTwo &&
			SearchTextThree &&
			SearchTextFour &&
			DBText;

		if (Valid && !Profiles.IsEmpty())
		{
			NameText->SetText(FText::FromString(Profiles[2].Name));
			HeightText->SetText(FText::FromString(Profiles[2].Height));
			WeightText->SetText(FText::FromString(Profiles[2].Weight));
			RaceText->SetText(FText::FromString(Profiles[2].Race));
			ProfileImage->SetBrushFromTexture(Profiles[2].ProfilePic);
			SelectedProfileImage->SetBrushFromTexture(Profiles[2].ProfilePic);
			EndProfileImage->SetBrushFromTexture(Profiles[2].ProfilePic);
			SelectedNameText->SetText(FText::FromString(Profiles[2].Name));
			CultSign->SetBrushFromTexture(Profiles[2].CultSign);
			SearchResultText->SetText(FText::FromString(Profiles[2].Name));
			SearchTextOne->SetText(FText::FromString(Profiles[2].SearchResults[0]));
			SearchTextTwo->SetText(FText::FromString(Profiles[2].SearchResults[1]));
			SearchTextThree->SetText(FText::FromString(Profiles[2].SearchResults[2]));
			SearchTextFour->SetText(FText::FromString(Profiles[2].SearchResults[3]));
			

			if (BioBox)
			{
				BioBox->ClearChildren();
				for (auto Line : Profiles[2].Bio)
				{
					UTextBlock* NewBioLine = NewObject<UTextBlock>(BioBox);
					if (NewBioLine)
					{
						NewBioLine->SetAutoWrapText(true);
						FSlateFontInfo FontInfo = NewBioLine->GetFont();
						FontInfo.Size = 16;
						NewBioLine->SetFont(FontInfo);
						NewBioLine->SetText(FText::FromString(Line));
						BioBox->AddChild(NewBioLine);
					}

					USizeBox* NewLineSpacer = NewObject<USizeBox>(BioBox);
					if (NewLineSpacer)
					{
						NewLineSpacer->SetMinDesiredHeight(BioSpacer);
						BioBox->AddChild(NewLineSpacer);
					}
				}

			}
			
			FString Hobbies;
			FString DBs;
			Hobbies.Append(TEXT("Hobbies: \n"));
			DBs.Append(TEXT("Dealbreakers: \n"));
			for (FString Hobby : Profiles[2].Hobbies)
			{
				Hobbies.Append(Hobby);
				Hobbies.Append(TEXT("\n"));
			}
			for (FString DB : Profiles[2].DealBreakers)
			{
				DBs.Append(DB);
				DBs.Append(TEXT("\n"));
			}
			HobbiesText->SetText(FText::FromString(Hobbies));
			DBText->SetText(FText::FromString(DBs));
		}

		if (FeedBox)
		{
			FeedBox->ClearChildren();
			for (auto Item : Profiles[2].Feed)
			{
				UTextBlock* NewPostText = NewObject<UTextBlock>(FeedBox);
				if (NewPostText)
				{
					NewPostText->SetAutoWrapText(true);
					NewPostText->SetText(FText::FromString(Item.Post));
					FeedBox->AddChild(NewPostText);
				}

				USizeBox* NewPostSpacer = NewObject<USizeBox>(FeedBox);
				if (NewPostSpacer)
				{
					NewPostSpacer->SetMinDesiredHeight(PostSpacer);
					FeedBox->AddChild(NewPostSpacer);
				}

				for (auto Comment : Item.Comments)
				{
					UTextBlock* NewCommentText = NewObject<UTextBlock>(FeedBox);
					if (NewCommentText)
					{
						NewCommentText->SetAutoWrapText(true);
						NewCommentText->SetText(FText::FromString(Comment));
						FeedBox->AddChild(NewCommentText);
					}

					USizeBox* NewCommentSpacer = NewObject<USizeBox>(FeedBox);
					NewCommentSpacer->SetMinDesiredHeight(CommentSpacer);
					if (NewCommentSpacer)
					{
						FeedBox->AddChild(NewCommentSpacer);
					}
				}

				if (Profiles[2].Feed.Num() > 1)
				{
					USizeBox* NewSeparator = NewObject<USizeBox>(FeedBox);
					if (NewSeparator)
					{
						NewSeparator->SetMinDesiredHeight(SeparatorSpace);
						FeedBox->AddChild(NewSeparator);
					}
				}
			}
		}
		
		SwitchGameMenu(ProfileScreen);
	}
}

void UMainMenu::BigTreeButtonPressed()
{
	if (DisabledButtons)
	{
		DisabledButtons = false;
	}

	if (ProfileScreen)
	{
		bool Valid =
			EndProfileImage &&
			ProfileImage &&
			SelectedProfileImage &&
			SelectedNameText &&
			NameText &&
			HeightText &&
			WeightText &&
			RaceText &&
			HobbiesText &&
			SearchResultText &&
			SearchTextOne &&
			SearchTextTwo &&
			SearchTextThree &&
			SearchTextFour &&
			DBText;

		if (Valid && !Profiles.IsEmpty())
		{
			NameText->SetText(FText::FromString(Profiles[3].Name));
			HeightText->SetText(FText::FromString(Profiles[3].Height));
			WeightText->SetText(FText::FromString(Profiles[3].Weight));
			RaceText->SetText(FText::FromString(Profiles[3].Race));
			ProfileImage->SetBrushFromTexture(Profiles[3].ProfilePic);
			SelectedProfileImage->SetBrushFromTexture(Profiles[3].ProfilePic);
			EndProfileImage->SetBrushFromTexture(Profiles[3].ProfilePic);
			SelectedNameText->SetText(FText::FromString(Profiles[3].Name));
			CultSign->SetBrushFromTexture(Profiles[3].CultSign);
			SearchResultText->SetText(FText::FromString(Profiles[3].Name));
			SearchTextOne->SetText(FText::FromString(Profiles[3].SearchResults[0]));
			SearchTextTwo->SetText(FText::FromString(Profiles[3].SearchResults[1]));
			SearchTextThree->SetText(FText::FromString(Profiles[3].SearchResults[2]));
			SearchTextFour->SetText(FText::FromString(Profiles[3].SearchResults[3]));

			if (BioBox)
			{
				BioBox->ClearChildren();
				for (auto Line : Profiles[3].Bio)
				{
					UTextBlock* NewBioLine = NewObject<UTextBlock>(BioBox);
					if (NewBioLine)
					{
						NewBioLine->SetAutoWrapText(true);
						FSlateFontInfo FontInfo = NewBioLine->GetFont();
						FontInfo.Size = 16;
						NewBioLine->SetFont(FontInfo);
						NewBioLine->SetText(FText::FromString(Line));
						BioBox->AddChild(NewBioLine);
					}

					USizeBox* NewLineSpacer = NewObject<USizeBox>(BioBox);
					if (NewLineSpacer)
					{
						NewLineSpacer->SetMinDesiredHeight(BioSpacer);
						BioBox->AddChild(NewLineSpacer);
					}
				}

			}
			
			FString Hobbies;
			FString DBs;
			Hobbies.Append(TEXT("Hobbies: \n"));
			DBs.Append(TEXT("Dealbreakers: \n"));
			for (FString Hobby : Profiles[3].Hobbies)
			{
				Hobbies.Append(Hobby);
				Hobbies.Append(TEXT("\n"));
			}
			for (FString DB : Profiles[3].DealBreakers)
			{
				DBs.Append(DB);
				DBs.Append(TEXT("\n"));
			}
			HobbiesText->SetText(FText::FromString(Hobbies));
			DBText->SetText(FText::FromString(DBs));
		}

		if (FeedBox)
		{
			FeedBox->ClearChildren();
			for (auto Item : Profiles[3].Feed)
			{
				UTextBlock* NewPostText = NewObject<UTextBlock>(FeedBox);
				if (NewPostText)
				{
					NewPostText->SetAutoWrapText(true);
					NewPostText->SetText(FText::FromString(Item.Post));
					FeedBox->AddChild(NewPostText);
				}

				USizeBox* NewPostSpacer = NewObject<USizeBox>(FeedBox);
				if (NewPostSpacer)
				{
					NewPostSpacer->SetMinDesiredHeight(PostSpacer);
					FeedBox->AddChild(NewPostSpacer);
				}

				for (auto Comment : Item.Comments)
				{
					UTextBlock* NewCommentText = NewObject<UTextBlock>(FeedBox);
					if (NewCommentText)
					{
						NewCommentText->SetAutoWrapText(true);
						NewCommentText->SetText(FText::FromString(Comment));
						FeedBox->AddChild(NewCommentText);
					}

					USizeBox* NewCommentSpacer = NewObject<USizeBox>(FeedBox);
					NewCommentSpacer->SetMinDesiredHeight(CommentSpacer);
					if (NewCommentSpacer)
					{
						FeedBox->AddChild(NewCommentSpacer);
					}
				}

				if (Profiles[3].Feed.Num() > 1)
				{
					USizeBox* NewSeparator = NewObject<USizeBox>(FeedBox);
					if (NewSeparator)
					{
						NewSeparator->SetMinDesiredHeight(SeparatorSpace);
						FeedBox->AddChild(NewSeparator);
					}
				}
			}
		}
		
		SwitchGameMenu(ProfileScreen);
	}
}

void UMainMenu::CthulhuButtonPressed()
{
	if (DisabledButtons)
	{
		DisabledButtons = false;
	}

	if (ProfileScreen)
	{
		bool Valid =
			EndProfileImage &&
			ProfileImage &&
			SelectedProfileImage &&
			SelectedNameText &&
			NameText &&
			HeightText &&
			WeightText &&
			RaceText &&
			HobbiesText &&
			SearchResultText &&
			SearchTextOne &&
			SearchTextTwo &&
			SearchTextThree &&
			SearchTextFour &&
			DBText;

		if (Valid && !Profiles.IsEmpty())
		{
			NameText->SetText(FText::FromString(Profiles[4].Name));
			HeightText->SetText(FText::FromString(Profiles[4].Height));
			WeightText->SetText(FText::FromString(Profiles[4].Weight));
			RaceText->SetText(FText::FromString(Profiles[4].Race));
			ProfileImage->SetBrushFromTexture(Profiles[4].ProfilePic);
			SelectedProfileImage->SetBrushFromTexture(Profiles[4].ProfilePic);
			EndProfileImage->SetBrushFromTexture(Profiles[4].ProfilePic);
			SelectedNameText->SetText(FText::FromString(Profiles[4].Name));
			CultSign->SetBrushFromTexture(Profiles[4].CultSign);
			SearchResultText->SetText(FText::FromString(Profiles[4].Name));
			SearchTextOne->SetText(FText::FromString(Profiles[4].SearchResults[0]));
			SearchTextTwo->SetText(FText::FromString(Profiles[4].SearchResults[1]));
			SearchTextThree->SetText(FText::FromString(Profiles[4].SearchResults[2]));
			SearchTextFour->SetText(FText::FromString(Profiles[4].SearchResults[3]));

			if (BioBox)
			{
				BioBox->ClearChildren();
				for (auto Line : Profiles[4].Bio)
				{
					UTextBlock* NewBioLine = NewObject<UTextBlock>(BioBox);
					if (NewBioLine)
					{
						NewBioLine->SetAutoWrapText(true);
						FSlateFontInfo FontInfo = NewBioLine->GetFont();
						FontInfo.Size = 16;
						NewBioLine->SetFont(FontInfo);
						NewBioLine->SetText(FText::FromString(Line));
						BioBox->AddChild(NewBioLine);
					}

					USizeBox* NewLineSpacer = NewObject<USizeBox>(BioBox);
					if (NewLineSpacer)
					{
						NewLineSpacer->SetMinDesiredHeight(BioSpacer);
						BioBox->AddChild(NewLineSpacer);
					}
				}

			}
			
			FString Hobbies;
			FString DBs;
			Hobbies.Append(TEXT("Hobbies: \n"));
			DBs.Append(TEXT("Dealbreakers: \n"));
			for (FString Hobby : Profiles[4].Hobbies)
			{
				Hobbies.Append(Hobby);
				Hobbies.Append(TEXT("\n"));
			}
			for (FString DB : Profiles[4].DealBreakers)
			{
				DBs.Append(DB);
				DBs.Append(TEXT("\n"));
			}
			HobbiesText->SetText(FText::FromString(Hobbies));
			DBText->SetText(FText::FromString(DBs));
		}

		if (FeedBox)
		{
			FeedBox->ClearChildren();
			for (auto Item : Profiles[4].Feed)
			{
				UTextBlock* NewPostText = NewObject<UTextBlock>(FeedBox);
				if (NewPostText)
				{
					NewPostText->SetAutoWrapText(true);
					NewPostText->SetText(FText::FromString(Item.Post));
					FeedBox->AddChild(NewPostText);
				}

				USizeBox* NewPostSpacer = NewObject<USizeBox>(FeedBox);
				if (NewPostSpacer)
				{
					NewPostSpacer->SetMinDesiredHeight(PostSpacer);
					FeedBox->AddChild(NewPostSpacer);
				}

				for (auto Comment : Item.Comments)
				{
					UTextBlock* NewCommentText = NewObject<UTextBlock>(FeedBox);
					if (NewCommentText)
					{
						NewCommentText->SetAutoWrapText(true);
						NewCommentText->SetText(FText::FromString(Comment));
						FeedBox->AddChild(NewCommentText);
					}

					USizeBox* NewCommentSpacer = NewObject<USizeBox>(FeedBox);
					NewCommentSpacer->SetMinDesiredHeight(CommentSpacer);
					if (NewCommentSpacer)
					{
						FeedBox->AddChild(NewCommentSpacer);
					}
				}

				if (Profiles[4].Feed.Num() > 1)
				{
					USizeBox* NewSeparator = NewObject<USizeBox>(FeedBox);
					if (NewSeparator)
					{
						NewSeparator->SetMinDesiredHeight(SeparatorSpace);
						FeedBox->AddChild(NewSeparator);
					}
				}
			}
		}
		
		SwitchGameMenu(ProfileScreen);
	}
}
