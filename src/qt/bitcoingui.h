#ifndef BITCOINGUI_H
#define BITCOINGUI_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#include <stdint.h>

//    Uncomment to build QUA Adv
//
//#include "radio.h"
//#include "bitcointalk.h"
//#include "twitter.h"
//#include "bittrex.h"
//#include "coinexchange.h"
//#include "yobit.h"

class TransactionTableModel;
class ClientModel;
class WalletModel;
class TransactionView;
class OverviewPage;
class AddressBookPage;
class SendCoinsDialog;
class SignVerifyMessageDialog;
class Notificator;
class RPCConsole;
class MasternodeManager;
class MessagePage;
class MessageModel;
class BlockBrowser;

QT_BEGIN_NAMESPACE
class QLabel;
class QModelIndex;
class QProgressBar;
class QStackedWidget;
class QScrollArea;
class QLineEdit;
class QTableView;
class QAbstractItemModel;
class QUrl;
QT_END_NAMESPACE

/**
  Bitcoin GUI main class. This class represents the main window of the Bitcoin UI. It communicates with both the client and
  wallet models to give the user an up-to-date view of the current core state.
*/
class BitcoinGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit BitcoinGUI(QWidget *parent = 0);
    ~BitcoinGUI();

    /** Set the client model.
        The client model represents the part of the core that communicates with the P2P network, and is wallet-agnostic.
    */
    void setClientModel(ClientModel *clientModel);
    /** Set the wallet model.
        The wallet model represents a bitcoin wallet, and offers access to the list of transactions, address book and sending
        functionality.
    */
    void setWalletModel(WalletModel *walletModel);
    void setMessageModel(MessageModel *messageModel);

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    ClientModel *clientModel;
    WalletModel *walletModel;
    MessageModel *messageModel;

    QToolBar *toolbar;

    QStackedWidget *centralStackedWidget;

    QWidget *overviewWidget;
    QScrollArea *overviewScroll;
    OverviewPage *overviewPage;
    QWidget *transactionsPage;
    AddressBookPage *addressBookPage;
    AddressBookPage *receiveCoinsPage;
    SendCoinsDialog *sendCoinsPage;
    SignVerifyMessageDialog *signVerifyMessageDialog;
    MasternodeManager *masternodeManagerPage;
    MessagePage *messagePage;
//    Uncomment to build QUA Adv
//
//    Radio *radioPage;
//    Bitcointalk *bitcointalkPage;
//    Twitter *twitterPage;
//    Bittrex *bittrexPage;
//    Coinexchange *coinexchangePage;
//    Yobit *yobitPage;
    QLabel* netLabel;
    BlockBrowser *blockBrowser;
    QLabel *labelEncryptionIcon;
    QLabel *labelStakingIcon;
    QLabel *labelConnectionsIcon;
    QLabel *labelBlocksIcon;
    QLabel *progressBarLabel;
    QProgressBar *progressBar;
#ifdef USE_NATIVE_I2P
    QLabel* labelI2PConnections;
    QLabel* labelI2POnly;
    QLabel* labelI2PGenerated;
#endif

    QMenuBar *appMenuBar;
    QAction *overviewAction;
    QAction *historyAction;
    QAction *quitAction;
    QAction *sendCoinsAction;
    QAction *addressBookAction;
    QAction *signMessageAction;
    QAction *verifyMessageAction;
    QAction *aboutAction;
    QAction *receiveCoinsAction;
    QAction *optionsAction;
    QAction *toggleHideAction;
    QAction *exportAction;
    QAction *encryptWalletAction;
    QAction *backupWalletAction;
    QAction *changePassphraseAction;
    QAction *unlockWalletAction;
    QAction *lockWalletAction;
    QAction *aboutQtAction;
    QAction *openRPCConsoleAction;
    QAction *masternodeManagerAction;
    QAction *messageAction;
    QAction *blockAction;
//    Uncomment to build QUA Adv
//
//    QAction *radioAction;
//    QAction *bitcointalkAction;
//    QAction *twitterAction;
//    QAction *bittrexAction;
//    QAction *coinexchangeAction;
//    QAction *yobitAction;

    QSystemTrayIcon *trayIcon;
    Notificator *notificator;
    TransactionView *transactionView;
    RPCConsole *rpcConsole;

    QMovie *syncIconMovie;
    /** Keep track of previous number of blocks, to detect progress */
    int prevBlocks;

    uint64_t nWeight;

    /** Create the main UI actions. */
    void createActions();
    /** Create the menu bar and sub-menus. */
    void createMenuBar();
    /** Create the toolbars */
    void createToolBars();
    /** Create system tray (notification) icon */
    void createTrayIcon();

    void clearWidgets();

public slots:
#ifdef USE_NATIVE_I2P
    void setNumI2PConnections(int count);
#endif
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set number of blocks shown in the UI */
    void setNumBlocks(int count);
    /** Set the encryption status as shown in the UI.
       @param[in] status            current encryption status
       @see WalletModel::EncryptionStatus
    */
    void setEncryptionStatus(int status);

    /** Notify the user of an event from the core network or transaction handling code.
       @param[in] title     the message box / notification title
       @param[in] message   the displayed text
       @param[in] modal     true to use a message box, false to use a notification
       @param[in] style     style definitions (icon and used buttons - buttons only for message boxes)
                            @see CClientUIInterface::MessageBoxFlags
    */
    void message(const QString &title, const QString &message, bool modal, unsigned int style);
    /** Asks the user whether to pay the transaction fee or to cancel the transaction.
       It is currently not possible to pass a return value to another thread through
       BlockingQueuedConnection, so an indirected pointer is used.
       https://bugreports.qt-project.org/browse/QTBUG-10440

      @param[in] nFeeRequired       the required fee
      @param[out] payFee            true to pay the fee, false to not pay the fee
    */
    void askFee(qint64 nFeeRequired, bool *payFee);
    void handleURI(QString strURI);


#ifdef USE_NATIVE_I2P
    void showGeneratedI2PAddr(const QString& caption, const QString& pub, const QString& priv, const QString& b32, const QString& configFileName);
#endif

private slots:
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
    /** Switch to address book page */
    void gotoAddressBookPage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage();
    /** Switch to block explorer*/
    void gotoBlockBrowser();
    /** Switch to masternode manager page*/
    void gotoMasternodeManagerPage();
    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");
    /** Switch to message page*/
    void gotoMessagePage();
//    Uncomment to build QUA Adv
//
//    /** Switch to radio page */
//    void gotoRadioPage();
//    /** Switch to bitcointalk page */
//    void gotoBitcointalkPage();
//    /** Switch to twitter page */
//    void gotoTwitterPage();
//    /** Switch to bittrex page */
//    void gotoBittrexPage();
//    /** Switch to coinexchange page */
//    void gotoCoinexchangePage();
//    /** Switch to yobit page */
//   void gotoYobitPage();
    /** Show configuration dialog */
    void optionsClicked();
    /** Show about dialog */
    void aboutClicked();
#ifndef Q_OS_MAC
    /** Handle tray icon clicked */
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
#endif
    /** Show incoming transaction notification for new transactions.

        The new items are those between start and end inclusive, under the given parent item.
    */
    void incomingTransaction(const QModelIndex & parent, int start, int end);
    void incomingMessage(const QModelIndex & parent, int start, int end);
    /** Encrypt the wallet */
    void encryptWallet();
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
    /** Ask for passphrase to unlock wallet temporarily */
    void unlockWallet();

    void lockWallet();

    /** Show window if hidden, unminimize when minimized, rise when obscured or show if hidden and fToggleHidden is true */
    void showNormalIfMinimized(bool fToggleHidden = false);
    /** simply calls showNormalIfMinimized(true) for use in SLOT() macro */
    void toggleHidden();

    void updateWeight();
    void updateStakingIcon();

    /** called by a timer to check if fRequestShutdown has been set **/
    void detectShutdown();

};

#endif // BITCOINGUI_H
