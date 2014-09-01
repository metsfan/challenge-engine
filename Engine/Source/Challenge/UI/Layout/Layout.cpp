#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/Layout.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	void Layout::Update(int deltaMillis)
	{
		View::Update(deltaMillis);

		if (this->GetParent()) {
			if (this->IsLayoutInvalid()) {
				this->Measure(this->GetParent()->GetSize());
			}
			
		}
	}

	void Layout::Measure(const Size &parentSize)
	{
		View::Measure(parentSize);

		this->PositionSubviews();

		const Size &sizeSpec = this->GetLayoutParams().size;
		if (sizeSpec.width == WRAP_CONTENT || sizeSpec.height == WRAP_CONTENT) {
			this->WrapToSubviews();
		}

		this->PostLayout();
	}
};