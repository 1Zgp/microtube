import QtQuick 2.6
import Sailfish.Silica 1.0
import com.verdanditeam.yt 1.0

ListItem {
    id: listItem
    height: Theme.paddingLarge*8
    contentHeight: Theme.paddingLarge*8

    onClicked: {
        if (video === undefined) return;
        YTPlaylist.setActiveRow(index)
        video.loadStreamUrl()
        if (!subPage)
            pageStack.push(Qt.resolvedUrl("../VideoPlayer.qml"),
                           { video: video, title: display, author: author, viewCount: viewCount, description: description })
    }

    property bool subPage: false

    Row {
        anchors.fill: parent
        Column {
            id: left
            width: listItem.width/2.3
            height: listItem.height
            leftPadding: Theme.paddingLarge
            topPadding: Theme.paddingSmall
            bottomPadding: Theme.paddingSmall

            Image {
                width: parent.width - Theme.paddingLarge
                height: parent.height - Theme.paddingSmall*2
                source: thumbnail !== undefined ? thumbnail : ""
                asynchronous: true
                cache: true
                fillMode: Image.PreserveAspectFit
            }
        }

        Column {
            width: listItem.width - left.width
            height: listItem.height
            padding: Theme.paddingLarge

            Label {
                text: display
                width: parent.width - Theme.paddingLarge*2
                truncationMode: TruncationMode.Fade
            }

            Label {
                text: author !== undefined ? author : ""
                width: parent.width - Theme.paddingLarge*2
                font.pixelSize: Theme.fontSizeExtraSmall
                truncationMode: TruncationMode.Fade
            }

            Row {
                Label {
                    text: (published !== undefined ? published : "") + (viewCount !== undefined ? "  -  " + viewCount + " views" : "")
                    font.pixelSize: Theme.fontSizeExtraSmall
                }
            }
        }
    }
}
