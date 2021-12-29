#include "DocxNumbering.h"


// Qt
#include <QByteArray>
#include <QBuffer>

// Calligra
#include <KoXmlWriter.h>
#include <OdfReaderContext.h>
#include <KoOdfStyleManager.h>
#include <KoOdfStyle.h>
#include <KoOdfStyleProperties.h>

// This filter
#include "DocxStyleHelper.h"


DocxNumbering::DocxNumbering()
{

}
