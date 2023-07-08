// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSocial
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Social Media")
	FString Post;

	UPROPERTY(EditAnywhere, Category = "Social Media")
	TArray<FString> Comments;

};

USTRUCT(BlueprintType)
struct FProfile
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Profile")
	FString Name;

	UPROPERTY(EditAnywhere, Category = "Profile")
	FString Bio;

	UPROPERTY(EditAnywhere, Category = "Profile")
	FString Height;

	UPROPERTY(EditAnywhere, Category = "Profile")
	FString Weight;

	UPROPERTY(EditAnywhere, Category = "Profile")
	FString Race;

	UPROPERTY(EditAnywhere, Category = "Profile")
	TArray<FString> Hobbies;

	UPROPERTY(EditAnywhere, Category = "Profile")
	TArray<FString> DealBreakers;

	UPROPERTY(EditAnywhere, Category = "Profile")
	class UTexture2D* ProfilePic;

	UPROPERTY(EditAnywhere, Category = "Profile")
	UTexture2D* CultSign;

	UPROPERTY(EditAnywhere, Category = "Profile")
	TArray<FSocial> Feed;

};

UCLASS()
class CTHULHUCRUSH_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void Setup();

	UFUNCTION()
	void SwitchMenu(class UWidget* Menu);

	UFUNCTION()
	void SwitchGameMenu(UWidget* Menu);

	UFUNCTION()
	void PlayButtonPressed();

	UFUNCTION()
	void HoverPlayButton();

	UFUNCTION()
	void UnHoverPlayButton();

	UFUNCTION()
	void HoverExitButton();

	UFUNCTION()
	void UnHoverExitButton();

	UFUNCTION()
	void IncreaseTextSize(class UTextBlock* Text);

	UFUNCTION()
	void DecreaseTextSize(UTextBlock* Text);

	UFUNCTION()
	void GalleryButtonPressed();

	UFUNCTION()
	void CharacterButtonPressed();

	UFUNCTION()
	void SearchButtonPressed();

	UFUNCTION()
	void SocialButtonPressed();

	UFUNCTION()
	void DictionaryButtonPressed();

	UFUNCTION()
	void HandbookButtonPressed();

	UFUNCTION()
	void PestilenceButtonPressed();

protected:

	virtual bool Initialize() override;

private:

	bool DisabledButtons = true;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* StartMenu;
	
	UPROPERTY(meta = (BindWidget))
	UWidget* Game;

	UPROPERTY(meta = (BindWidget))
	UWidget* EndScreen;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* GameSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* ProfileScreen;

	UPROPERTY(meta = (BindWidget))
	UWidget* GalleryScreen;

	UPROPERTY(meta = (BindWidget))
	UWidget* CharacterScreen;

	UPROPERTY(meta = (BindWidget))
	UWidget* SearchScreen;

	UPROPERTY(meta = (BindWidget))
	UWidget* SocialScreen;

	UPROPERTY(meta = (BindWidget))
	UWidget* DictionaryScreen;

	UPROPERTY(meta = (BindWidget))
	UWidget* HandbookScreen;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExitText;

	UPROPERTY(EditAnywhere)
	TArray<FProfile> Profiles;

	UPROPERTY(meta = (BindWidget))
	class UImage* ProfileImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BioText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HeightText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeightText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RaceText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HobbiesText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DBText;

	UPROPERTY(meta = (BindWidget))
	UButton* GalleryButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PestilenceButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CharacterButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SearchButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SocialButton;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* FeedBox;

	UPROPERTY(EditAnywhere, Category = "Social Media")
	float PostSpacer = 30.f;
	
	UPROPERTY(EditAnywhere, Category = "Social Media")
	float CommentSpacer = 15.f;
	
	UPROPERTY(EditAnywhere, Category = "Social Media")
	float SeparatorSpace = 50.f;

	UPROPERTY(meta = (BindWidget))
	UButton* DictionaryButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Dictionary;

	UPROPERTY(meta = (BindWidget))
	UButton* HandbookButton;

	
};
