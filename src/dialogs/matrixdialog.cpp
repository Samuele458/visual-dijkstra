#include "dialogs/matrixdialog.h"

MatrixTableWidget::MatrixTableWidget( Graph* graph, QWidget* parent ) :
    QTableWidget(parent), AdjacencyMatrix(graph)
{
    QVector<QVector<int>> matrixVector = getMatrix();
    int side = matrixVector.length();


    setRowCount(side);
    setColumnCount(side);



    setHorizontalHeaderLabels( getNodes() );
    setVerticalHeaderLabels( getNodes() );

    QHeaderView* header = horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header = verticalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setDefaultAlignment(Qt::AlignCenter);

    QFont font;
    font.setPixelSize(24);

    for( int i = 0; i < side; i++ ) {
        for( int j = 0; j < side; j++ ) {
            QTableWidgetItem* item = new QTableWidgetItem( QString::number( matrixVector[i][j] ) );
            item->setTextAlignment(Qt::AlignCenter);
            item->setFont( font );
            setItem( i, j, item );

        }
    }

    verticalHeader()->setVisible(true);
    horizontalHeader()->setVisible(true);
}


void MatrixTableWidget::paintEvent(QPaintEvent* event)
{
    QTableWidget::paintEvent( event );

    if( getNodes().length() == 0 ) {
        QFont font;
        font.setPixelSize(20);

        QPainter painter(viewport());
        painter.setFont(font);

        painter.drawText(viewport()->width()/2-80,
                         viewport()->height()/2-50,
                         160,
                         100,
                         Qt::AlignCenter,
                         "Empty graph");
    }

    verticalHeader()->setVisible(true);
    horizontalHeader()->setVisible(true);


}

MatrixDialog::MatrixDialog( Graph* graph, QWidget* parent ) :
    QDialog( parent )
{
    this->setWindowTitle("Adjacency Matrix");
    this->setMinimumSize( 400, 400 );

    closeButton = new QPushButton("Close");
    csvExportButton = new QPushButton("Export CSV");

    buttons = new QHBoxLayout();
    buttons->addWidget(csvExportButton);
    buttons->addStretch();
    buttons->addWidget(closeButton);

    matrixTable = new MatrixTableWidget( graph );

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(matrixTable);
    mainLayout->addLayout(buttons);

    this->setLayout( mainLayout );

    connect( closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
    connect( csvExportButton, SIGNAL(clicked()), this, SLOT(csvExportButtonClicked()));


}

void MatrixDialog::closeButtonClicked() {
    this->close();
}

void MatrixDialog::csvExportButtonClicked() {
    QString filename = QFileDialog::getSaveFileName( this, "Save as...", "", "Csv (*.csv);;Others (*.*)" );

    if( filename != "" ) {
        QFile file(filename);

        if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QTextStream stream(&file);

            QVector<QVector<int>> matrixVector = matrixTable->getMatrix();

            for( int i = 0; i < matrixVector.length(); ++i ) {
                for( int j = 0; j < matrixVector.length(); ++j ) {
                    stream << matrixVector[i][j];
                    if( j != matrixVector.length() - 1 ) stream << ", ";
                }
                stream << "\n";
            }


            file.close();
        }
    }
}




