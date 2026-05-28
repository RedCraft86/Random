#include "Widgets/ExpressiveTextBlock.h"
#include "Styles/ExpressiveTextStyle.h"

#define DefaultStylePath TEXT("/ExpressiveText/Core/Internal/ExpressiveTextDefaultStyle.ExpressiveTextDefaultStyle")

FExpressiveTextData::FExpressiveTextData(): bUseAsset(false)
{
	TextFields.DefaultFontSize = 24;
	TextFields.UseDefaultFontSize = true;
	TextFields.WrapSettings.Value = 1.0f;
	TextFields.WrapSettings.ValueType = EExpressiveTextWrapMode::WrapAtPercentageOfParentSize;
	TextFields.DefaultStyle = LoadObject<UExpressiveTextStyle>(nullptr, DefaultStylePath);
}

int64 FExpressiveTextData::CalcChecksum() const
{
	int64 Result = TextFields.CalcChecksum();
	Result = HashCombine(Result, GetTypeHash(bUseAsset));
	Result = HashCombine(Result, GetTypeHash(TextAsset));
	if (TextAsset) Result = HashCombine(Result, TextAsset->CalcChecksum());
	return Result;
}

FExpressiveText FExpressiveTextData::GetExpressiveText()
{
	FExpressiveText Result;
	if (bUseAsset)
	{
		ensureAlwaysMsgf(!FApp::IsGame() || IsValid(TextAsset), TEXT("Cannot use TextAsset, it is nullptr!"));
		Result.SetFields(TextAsset->Fields);
	}
	else
	{
		Result.SetFields(TextFields);
		if (!Result.GetDefaultStyle())
		{
			// Recommended not to rely on this, explicitly set your style when possible
			TextFields.DefaultStyle = LoadObject<UExpressiveTextStyle>(nullptr, DefaultStylePath);
			Result.SetDefaultStyle(TextFields.DefaultStyle);
		}
	}
	
	return Result;
}

void FExpressiveTextData::SetText(const FText& InText, const bool bUseFieldsFromAsset)
{
	if (bUseFieldsFromAsset && TextAsset) SetTextFields(TextAsset->Fields);
	TextFields.Text = InText;
	bUseAsset = false;
}

void FExpressiveTextData::SetTextFields(const FExpressiveTextFields& InFields)
{
	bUseAsset = false;
	TextFields = InFields;
}

void FExpressiveTextData::SetTextAsset(UExpressiveTextAsset* InAsset)
{
	bUseAsset = true;
	TextAsset = InAsset;
}

void UExpressiveTextBlock::OverrideExpressiveText(const FExpressiveTextData& InText)
{
	ExpressiveText = InText;
	UpdateText();
}

void UExpressiveTextBlock::SetText(const FText InText, const bool bUseFieldsFromAsset)
{
	ExpressiveText.SetText(InText, bUseFieldsFromAsset);
	UpdateText();
}

void UExpressiveTextBlock::SetTextFields(const FExpressiveTextFields& InFields)
{
	ExpressiveText.SetTextFields(InFields);
	UpdateText();
}

void UExpressiveTextBlock::SetTextAsset(UExpressiveTextAsset* InAsset)
{
	ExpressiveText.SetTextAsset(InAsset);
	UpdateText();
}

void UExpressiveTextBlock::UpdateText()
{
	CachedSize = CurrentSize;
	CachedChecksum = ExpressiveText.CalcChecksum();
	FExpressiveText GenExprText = ExpressiveText.GetExpressiveText();
	GenExprText.DefineWorldContext(this);
	SetExpressiveText(GenExprText);
}

bool UExpressiveTextBlock::IsCacheInvalid() const
{
	return CachedChecksum != ExpressiveText.CalcChecksum()
		|| !CachedSize.Equals(CurrentSize, 0.001f);
}

EActiveTimerReturnType UExpressiveTextBlock::UpdateSize(double CurrentTime, float DeltaTime)
{
	CurrentSize = GetCachedGeometry().GetLocalSize();
	if (IsCacheInvalid()) UpdateText();
	return EActiveTimerReturnType::Continue;
}

TSharedRef<SWidget> UExpressiveTextBlock::RebuildWidget()
{
	TSharedRef<SWidget> Widget = Super::RebuildWidget();
	Widget->RegisterActiveTimer(0.1f, FWidgetActiveTimerDelegate::CreateUObject(this, &UExpressiveTextBlock::UpdateSize));
	return Widget;
}

void UExpressiveTextBlock::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	CurrentSize = GetCachedGeometry().GetLocalSize();
	UpdateText();
}

#undef DefaultStylePath
