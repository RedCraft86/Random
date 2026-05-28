#pragma once

#include "CoreMinimal.h"
#include "Asset/ExpressiveTextAsset.h"
#include "ExpressiveTextRendererWidget.h"
#include "ExpressiveTextBlock.generated.h"

USTRUCT(BlueprintType)
struct EXPRESSIVETEXT_API FExpressiveTextData final
{
	GENERATED_BODY()

	FExpressiveTextData();
	int64 CalcChecksum() const;
	FExpressiveText GetExpressiveText();
	void SetText(const FText& InText, const bool bUseFieldsFromAsset = false);
	void SetTextFields(const FExpressiveTextFields& InFields);
	void SetTextAsset(UExpressiveTextAsset* InAsset);
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ExpressiveText, meta = (AllowPrivateAccess = true))
		bool bUseAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ExpressiveText, meta = (EditCondition = "!bUseAsset", EditConditionHides, AllowPrivateAccess = true, ShowOnlyInnerProperties))
		FExpressiveTextFields TextFields;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ExpressiveText, meta = (EditCondition = "bUseAsset", EditConditionHides, AllowPrivateAccess = true))
		TObjectPtr<UExpressiveTextAsset> TextAsset;
};

UCLASS(DisplayName = "Expressive Text")
class EXPRESSIVETEXT_API UExpressiveTextBlock final : public UExpressiveTextRendererWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Content, meta = (ShowOnlyInnerProperties))
		FExpressiveTextData ExpressiveText;

	UFUNCTION(BlueprintCallable, Category = "Expressive Text Block")
		void OverrideExpressiveText(const FExpressiveTextData& InText);

	UFUNCTION(BlueprintCallable, Category = "Expressive Text Block")
		void SetText(const FText InText, const bool bUseFieldsFromAsset = true);

	UFUNCTION(BlueprintCallable, Category = "Expressive Text Block")
		void SetTextFields(const FExpressiveTextFields& InFields);

	UFUNCTION(BlueprintCallable, Category = "Expressive Text Block")
		void SetTextAsset(UExpressiveTextAsset* InAsset);

private:

	int64 CachedChecksum = 0;
	FVector2D CurrentSize = FVector2D::ZeroVector;
	FVector2D CachedSize = FVector2D::ZeroVector;

	void UpdateText();
	bool IsCacheInvalid() const;

	EActiveTimerReturnType UpdateSize(double CurrentTime, float DeltaTime);

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("UMG", "Common", "Common"); }
	virtual void OnCreationFromPalette() override
	{
		SetText(NSLOCTEXT("ExpressiveText", "ExprTextBlock", "[32rr](Expressive Text)"));
		SetVisibility(ESlateVisibility::HitTestInvisible);
	}
#endif



/**
 * Statics for FExpressiveTextData
 */
public: 

	UFUNCTION(BlueprintCallable, Category = ExpressiveTextData, DisplayName = "Get Expressive Text")
	static FExpressiveText GetExpressiveTextData(UPARAM(ref) FExpressiveTextData& InData)
	{
		return InData.GetExpressiveText();
	}

	UFUNCTION(BlueprintCallable, Category = ExpressiveTextData, DisplayName = "Set Text")
	static void SetTextData(UPARAM(ref) FExpressiveTextData& InData, const FText InText, const bool bUseFieldsFromAsset = false)
	{
		InData.SetText(InText, bUseFieldsFromAsset);
	}

	UFUNCTION(BlueprintCallable, Category = ExpressiveTextData, DisplayName = "Set Text Fields")
	static void SetTextFieldsData(UPARAM(ref) FExpressiveTextData& InData, const FExpressiveTextFields& InFields)
	{
		InData.SetTextFields(InFields);
	}

	UFUNCTION(BlueprintCallable, Category = ExpressiveTextData, DisplayName = "Set Text Asset")
	static void SetTextAssetData(UPARAM(ref) FExpressiveTextData& InData, UExpressiveTextAsset* InAsset)
	{
		InData.SetTextAsset(InAsset);
	}
};
