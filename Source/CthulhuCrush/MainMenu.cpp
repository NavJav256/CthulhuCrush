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

	return true;
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
			ProfileImage &&
			NameText &&
			BioText &&
			HeightText &&
			WeightText &&
			RaceText &&
			HobbiesText &&
			DBText;

		if (Valid && !Profiles.IsEmpty())
		{
			NameText->SetText(FText::FromString(Profiles[0].Name));
			BioText->SetText(FText::FromString(Profiles[0].Bio));
			HeightText->SetText(FText::FromString(Profiles[0].Height));
			WeightText->SetText(FText::FromString(Profiles[0].Weight));
			RaceText->SetText(FText::FromString(Profiles[0].Race));
			ProfileImage->SetBrushFromTexture(Profiles[0].ProfilePic);
			/*
			FString Hobbies = FString(TEXT("Hobbies:\n"));
			FString DBs = FString(TEXT("Deal Breakers:\n"));
			for (FString Hobby : Profiles[0].Hobbies)
			{
				Hobbies.Append(FString::Printf("- %s \n", *Hobby));
			}
			for (FString DB : Profiles[0].DealBreakers)
			{
				DBs.Append(FString::Printf("- %s \n", *DB));
			}
			HobbiesText->SetText(FText::FromString(Hobbies));
			DBText->SetText(FText::FromString(DBs));
			*/
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
