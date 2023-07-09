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
	class UTexture2D* ProfilePic;

	UPROPERTY(EditAnywhere, Category = "Profile")
	UTexture2D* CultSign;

	UPROPERTY(EditAnywhere, Category = "Profile")
	TArray<FString> Bio;

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
	TArray<FSocial> Feed;

	UPROPERTY(EditAnywhere, Category = "Profile")
	TArray<FString> SearchResults;

};

USTRUCT(BlueprintType)
struct FTrait
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Trait")
	FString TraitName;

	UPROPERTY(EditAnywhere, Category = "Trait")
	TArray<FString> Disqualifies;

	UPROPERTY(VisibleAnywhere, Category = "Trait")
	bool bOwning;

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

	UFUNCTION()
	void WidowButtonPressed();

	UFUNCTION()
	void GruudButtonPressed();

	UFUNCTION()
	void BigTreeButtonPressed();

	UFUNCTION()
	void CthulhuButtonPressed();

	UFUNCTION()
	void ConfirmButtonPressed();

	UFUNCTION()
	void HoverConfirmButton();

	UFUNCTION()
	void UnHoverConfirmButton();

protected:

	virtual bool Initialize() override;

	void CreateTraitPool();

	void SelectCharacterTraits();

	void ShuffleArray(TArray<FTrait> &Array);

private:

	int32 ProfileNum;

	bool DisabledButtons = true;

	UPROPERTY(EditAnywhere)
	TArray<FTrait> Traits;

	UPROPERTY(VisibleAnywhere)
	TArray<FTrait> TraitPool;

	UPROPERTY(EditAnywhere)
	int32 NumOfOwningTraits;

	UPROPERTY(VisibleAnywhere)
	FString CorrectAnswer;

	UPROPERTY(VisibleAnywhere)
	FString SelectedAnswer;

	UPROPERTY(VisibleAnywhere)
	TArray<FTrait> OwningTraits;

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
	UTextBlock* SearchResultText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SearchTextOne;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SearchTextTwo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SearchTextThree;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SearchTextFour;

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
	UImage* CultSign;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* BioBox;

	UPROPERTY(EditAnywhere, Category = "Bio")
	float BioSpacer = 20.f;

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
	UButton* WidowButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GruudButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BigTreeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CthulhuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CharacterButton;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* TraitsBox;

	UPROPERTY(EditAnywhere, Category = "Traits")
	float TraitSpacer = 15.f;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedNameText;

	UPROPERTY(meta = (BindWidget))
	UImage* SelectedProfileImage;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UImage* EndProfileImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EndScreenText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConfirmText;

	UPROPERTY(meta = (BindWidget))
	UButton* SearchButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SocialButton;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* FeedBox;

	UPROPERTY(EditAnywhere, Category = "Social Media")
	float PostSpacer = 30.f;
	
	UPROPERTY(EditAnywhere, Category = "Social Media")
	float CommentSpacer = 15.f;
	
	UPROPERTY(EditAnywhere, Category = "Social Media")
	float SeparatorSpace = 50.f;

	UPROPERTY(meta = (BindWidget))
	UButton* DictionaryButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HandbookButton;

	
};
