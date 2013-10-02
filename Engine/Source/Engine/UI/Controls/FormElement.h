#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/View.h>

namespace challenge
{
	class FormElement : public View
	{
	public:
		FormElement(Frame frame = Frame()) : View(frame) {}

		void SetName(const std::string &name) { mName = name; }
		const std::string& GetName() { return mName; }

		virtual void SetValue(const std::string &value) = 0;
		virtual std::string GetValue() = 0;

	private:
		std::string mName;
	};

	class MultiFormElement : public View
	{
	public:
		MultiFormElement(Frame frame = Frame()) : View(frame) {}

		void SetName(const std::string &name) { mName = name; }
		const std::string& GetName() { return mName; }

		virtual int GetNumValues() = 0;
		virtual void SetValue(int index, const std::string &value) = 0;
		virtual std::string GetValue(int index) = 0;

	private:
		std::string mName;
	};
};