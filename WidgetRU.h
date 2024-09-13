

#ifndef WIDGETRU_H
#define WIDGETRU_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>
#include <QRect>

class TagItemDelegate : public QStyledItemDelegate
{
public:
    TagItemDelegate(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase()) : QStyledItemDelegate(parent), m_db(db) {}

    // 重写 paint() 方法以自定义绘制
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::paint(painter, option, index);

        // 获取文件路径
        QString filePath = index.data(QFileSystemModel::FilePathRole).toString();

        if (hasTags(filePath)) {
//            QRect rect = option.rect;
//            QPen pen(Qt::red);  // 红色边框
//            pen.setWidth(2);
//            painter->setPen(pen);
//            painter->drawRect(rect.adjusted(0, 0, -1, -1));  // 绘制边框
            // 绘制标识 (例如，绘制一个小图标)
            QRect rect = option.rect;
            QRect iconRect(rect.right() - 16, rect.top(), 16, 16); // 自定义图标位置
            QIcon tagIcon(":/image/application_go.svg"); // 自定义图标
            tagIcon.paint(painter, iconRect, Qt::AlignCenter);
        }
    }

private:
    QSqlDatabase m_db;
    bool hasTags(const QString &filePath) const
    {

        QSqlQuery query(m_db);
        query.prepare("SELECT COUNT(*) FROM FilePaths  WHERE file_path = :filePath");
        query.bindValue(":filePath", filePath);

        if (!query.exec()) {
            qDebug() << "Query execution error:" << query.lastError().text();
            return false;
        }

        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0;
        }

        return false;
    }
};


namespace Ui {
    class WidgetRU;
}

class WidgetRU : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRU(QWidget *parent = nullptr);
    ~WidgetRU();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void fileOpened(const QString &filePath);

private slots:
    void onItemClicked(const QModelIndex &index);
    void saveMetadata(const QString &filePath, const QStringList &tags, const QString &annotation);

    void goButtonClicked();

    void on_saveButton_clicked();

private:
    Ui::WidgetRU *ui;
    QFileSystemModel *fileSystemModel;
};

#endif // WIDGETRU_H


