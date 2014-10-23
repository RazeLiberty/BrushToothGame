//
//  AchievementList.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//

#include "AchievementList.h"
// on "init" you need to initialize your instance
bool AchievementList::init()
{
    m_window_size = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    m_window_size.height -= 128;

    //画面サイズサイズを取得
    TableView* tableView = TableView::create(this, m_window_size);
    //展開方向
    tableView->setDirection(TableView::Direction::VERTICAL);
    //表示順序上からしたへ
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    //追加
    tableView->setDelegate(this);
    m_pLayer->addChild(tableView);
    tableView->reloadData();
    tableView->setPosition(Vec2(0,128));

    
    return true;
}
AchievementList* AchievementList::create(Layer* layer)
{
    AchievementList* achievelist = new AchievementList;
    achievelist->m_pLayer = layer;
    achievelist->init();
    return achievelist;
}

// セルの大きさを設定する
Size AchievementList::cellSizeForTable(TableView *table){
    return Size(m_window_size.width, CELL_SIZE);
}

// 1セルに表示させるValueをセット
TableViewCell* AchievementList::tableCellAtIndex(TableView *table, ssize_t idx)
{
    std::string id = StringUtils::format("%zd", idx);
    std::string Title = StringUtils::format("Title %zd", idx);
    std::string text = StringUtils::format("Message %zd", idx);
    TableViewCell *cell = table->dequeueCell();
    
    cell = new TableViewCell();
    cell->autorelease();
    // セルの背景は交互に色を変更する
    auto background_color = Color3B(255,255,255);
    if (idx%2) {
        background_color = Color3B(200,200,200);
    }
    
    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, m_window_size.width, CELL_SIZE));
    bg->setColor(background_color);
    bg->setTag(100);
    cell->addChild(bg);
    
    
    // ID部分
    auto *label_1 = LabelTTF::create(id.c_str(), "Arial", ACHIEVE_TITLE_SIZE);
    label_1->setAnchorPoint(Point(0, 0));
    label_1->setPosition(Point(25,label_1->getContentSize().height / 2));
    label_1->setColor(Color3B(0,0,0));
    cell->addChild(label_1);
    
    // タイトル部分
    auto *label_2 = LabelTTF::create(Title.c_str(), "Arial", ACHIEVE_TITLE_SIZE);
    label_2->setAnchorPoint(Point(0, 0));
    label_2->setPosition(Point(50 + label_1->getContentSize().width, label_2->getContentSize().height / 2));
    label_2->setColor(Color3B(0,0,0));
    cell->addChild(label_2);
    
    // メッセージ部分
    auto *label_3 = LabelTTF::create(text.c_str(), "Arial", ACHIEVE_MESSAGE_SIZE);
    label_3->setAnchorPoint(Point(0, 0));
    label_3->setPosition(Point(50 + label_1->getContentSize().width,5));
    label_3->setColor(Color3B(0,0,0));
    cell->addChild(label_3);
    return cell;
}

// セル数
ssize_t AchievementList::numberOfCellsInTableView(TableView *table){
    return 40;
}

// セルがタッチされた時のcallback
void AchievementList::tableCellTouched(TableView* table, TableViewCell* cell){
    CCLOG("%ziのセルがタッチされました", cell->getIdx());
}