import { SerialContext } from "../SerialContext";
import "./DeviceSetting.css";
import React, { useContext, useState } from "react";



function DeviceSetting() {
  const { sendMessage, readMessage, receivedMessage } = useContext(SerialContext);
  const [message, setMessage] = useState("");

  const handleSend = () => {
    sendMessage(message);
  };
  return (
    <div className="device-setting">
      <h2 className="title">Cấu hình Bluetooth</h2>

      {/* Thông tin thiết bị */}
      <div className="device-info">
        <div className="info-item">
          <label>Tên thiết bị:</label>
          <input type="text" placeholder="Nhập tên thiết bị" />
        </div>
        <div className="info-item">
          <label>Độ trễ giữa các phím:</label>
          <input type="number" />
        </div>
      </div>

      {/* Cấu hình nút bấm */}
      <div className="button-config">
        <h3>Cấu hình nút bấm</h3>
        <label>Button 1:</label>
        <div className="info-item">
          <input type="text" placeholder="Nhập mã cấu hình button. Ví dụ: {SHIFT}H{~SHIFT}ello" />
        </div>
        <label>Button 2:</label>
        <div className="info-item">
          <input type="text" placeholder="Nhập mã cấu hình button. Ví dụ: {SHIFT}H{~SHIFT}ello" />
        </div>
        <label>Button 3:</label>
        <div className="info-item">
          <input type="text" placeholder="Nhập mã cấu hình button. Ví dụ: {SHIFT}H{~SHIFT}ello" />
        </div>
        <label>Button 4:</label>
        <div className="info-item">
          <input type="text" placeholder="Nhập mã cấu hình button. Ví dụ: {SHIFT}H{~SHIFT}ello" />
        </div>
      </div>
      <div className="actions">
        <button className="check-btn">Cập nhật thiết lập cho button</button>
      </div>
      {/* Tính năng nâng cao */}
      <div className="advanced">
        <h3>Advance for Experts</h3>
        <div>
          <label>Send message:</label>
          <textarea placeholder="Nhập tin nhắn gửi..." />
        </div>
        <div>
          <label>Receive message:</label>
          <textarea placeholder="Nhận tin nhắn..." />
        </div>
      </div>

      {/* Các nút hành động */}
      
    </div>
  );
}

export default DeviceSetting;
