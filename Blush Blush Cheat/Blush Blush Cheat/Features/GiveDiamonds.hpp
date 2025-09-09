#pragma once
#include "Feature.hpp"

// Utilities
// Token: 0x06000983 RID: 2435 RVA: 0x00039DF8 File Offset: 0x00037FF8
// public static bool AwardDiamonds(int amount)
// Utilities.AwardDiamonds(int amount)

class GiveDiamonds : public Feature
{
private:
	int amount = 1000000;

	void AddDiamonds(int amount)
	{
		MonoMethod* AwardDiamonds = Mono::Instance().GetMethod("Utilities", "AwardDiamonds", 2);
		if (AwardDiamonds == nullptr)
		{
			LogError("GiveDiamonds", "Unable to retrieve a pointer to Utilities.AwardDiamonds");
			return;
		}

		bool forceDiamonds = true; // ensure it always adds
		void* args[2] = { &amount, &forceDiamonds };

		MonoObject* result = Mono::Instance().Invoke(AwardDiamonds, nullptr, args);

		if (bExtraDebug && result != nullptr)
			LogInvoke("GiveDiamonds", "AwardDiamonds returned: " + std::to_string(*(bool*)Mono::Instance().GetValue(result)));
	}

public:
	GiveDiamonds() {};

	void Render() override
	{
		ImGui::Text("Diamonds");
		ImGui::InputInt("##DiamondAmount", &amount);
		ImGui::SameLine();
		if (ImGui::Button("Add"))
			AddDiamonds(amount);
	}

	void Create() override { Log("GiveDiamonds", "Initalized"); }
	
	void Destroy() override { Log("GiveDiamonds", "Destroyed"); }
};
