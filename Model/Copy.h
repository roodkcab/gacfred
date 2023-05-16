#pragma once
#include "UI/Source/Gacfred.h"

namespace gacfred
{
	class Copy : public vl::Object, public virtual gacfred::ICopy
	{
	private:
		vl::WString	Idx;
        CopyType Type;
		vl::WString	Content;
		vl::vint64_t Ctime;
        bool SeparatorVisible;

	public:
		Copy();
		Copy(const vl::WString& _idx, const CopyType _type, const vl::WString& _content);
		Copy(const Copy& copy);
        Copy(const Copy& copy, const vl::WString& search);

        vl::WString GetIdx()const override;
        void SetIdx(const vl::WString& _idx)override;
        CopyType GetType()const override;
        void SetType(CopyType _type)override;
		vl::WString GetContent()const override;
		void SetContent(const vl::WString& _content)override;
		vl::vint64_t GetCtime()const override;
		void SetCtime(vl::vint64_t _ctime)override;
        bool GetSeparatorVisible()override;
        void SetSeparatorVisible(bool visible)override;

        vl::WString GetShowtime()override;
        vl::Ptr<vl::presentation::DocumentModel> GetRichContent(bool full)override;
	};
}
