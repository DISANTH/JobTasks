import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import Path 1.0
import Job 1.0
import Task 1.0

Item {
    Column{
        ComboBox{
            id:comboFiles
            anchors.horizontalCenter: horizontalCenter
            width: 200
            editable: true
            onCurrentIndexChanged:{
                paths.activePath = currentIndex
                jobModel.jobs_ = paths.activeJobs
                comboJob.currentIndex = -1;
            }

            model: PathModel {
                paths: paths
            }
            onAccepted: {
                var x = combo.find(currentText);
                console.log("onAccepted Called x:: "+x);
                if (x === -1) {
                    model.append({modelData: editText})
                    currentIndex = combo.find(editText)
                }
            }
        }
        ComboBox{
            id:comboJob
            anchors.horizontalCenter: horizontalCenter
            width: 200
            editable: true
            onCurrentIndexChanged:{
                paths.activeJob = currentIndex
                taskModel.tasks = paths.activeTasks
                comboTask.currentIndex = -1;
            }
            model: JobModel {
                id: jobModel
            }

            onAccepted: {
                var x = combo.find(currentText);
                console.log("onAccepted Called x:: "+x);
                if (x === -1) {
                    model.append({modelData: editText})
                    currentIndex = combo.find(editText)
                }
            }
        }
        ComboBox{
            id:comboTask
            anchors.horizontalCenter: horizontalCenter
            width: 200
            editable: true
            model: TaskModel {
                id: taskModel
            }
            onAccepted: {
                var x = combo.find(currentText);
                console.log("onAccepted Called x:: "+x);
                if (x === -1) {
                    model.append({modelData: editText})
                    currentIndex = combo.find(editText)
                }
            }
        }
    }
}
