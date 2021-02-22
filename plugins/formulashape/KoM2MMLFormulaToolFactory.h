#include <KoToolFactoryBase.h>


class KoM2MMLFormulaToolFactory : public KoToolFactoryBase {
public:
    /// The constructor - reimplemented from KoToolFactoryBase
    explicit KoM2MMLFormulaToolFactory();

    /// The destructor - reimplemented from KoToolFactoryBase
    ~KoM2MMLFormulaToolFactory() override;

    /// @return an instance of KoFormulaTool
    KoToolBase* createTool( KoCanvasBase* canvas ) override;
};
