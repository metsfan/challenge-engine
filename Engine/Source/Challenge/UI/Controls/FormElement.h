#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	class FormElement : public View
	{
	public:
		FormElement(Frame frame = Frame()) : View(frame) {}
		virtual ~FormElement() {}

		void SetName(const std::string &name) { mName = name; }
		const std::string& GetName() { return mName; }

		virtual void SetValue(const std::string &value) = 0;
		virtual std::string GetValue() = 0;

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		std::string mName;
	};

	class MultiFormElement : public View
	{
	public:
		MultiFormElement(Frame frame = Frame()) : View(frame) {}
		virtual ~MultiFormElement() {}

		void SetName(const std::string &name) { mName = name; }
		const std::string& GetName() { return mName; }

		virtual int GetNumValues() = 0;
		virtual void SetValue(int index, const std::string &value) = 0;
		virtual std::string GetValue(int index) = 0;

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		std::string mName;
	};
};