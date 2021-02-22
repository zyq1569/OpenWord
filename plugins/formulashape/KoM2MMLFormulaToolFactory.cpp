#include "KoM2MMLFormulaToolFactory.h"

#include "KoM2MMLForumulaTool.h"

#include <KoIcon.h>
#include "FormulaCommand.h"


KoM2MMLFormulaToolFactory::KoM2MMLFormulaToolFactory():KoToolFactoryBase("KoM2MMLFormulaToolFactoryId")
{
#ifdef HAVE_M2MML
    setToolTip( i18n( "Edit formula with LaTeX/Matlab syntax" ) );
#else
    setToolTip( i18n( "Edit formula with LaTeX syntax" ) );
#endif
    setToolType( dynamicToolType() );
    setIconName(koIconName("edittext"));
    setPriority( 1 );
    setActivationShapeId( KoFormulaShapeId );
}

KoM2MMLFormulaToolFactory::~KoM2MMLFormulaToolFactory()
{

}

KoToolBase* KoM2MMLFormulaToolFactory::createTool( KoCanvasBase* canvas )
{
    return new KoM2MMLFormulaTool( canvas );
}
